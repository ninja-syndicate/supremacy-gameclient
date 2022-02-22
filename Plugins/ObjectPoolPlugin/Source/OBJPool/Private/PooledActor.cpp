//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2017 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PooledActor.h"
#include "OBJPool_Shared.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledActor::APooledActor(const FObjectInitializer &OBJ) : Super(OBJ) {
	InitialLifeSpan = 0.f;
	LifeSpanPool = 0.f;
	//
	SharedPool = nullptr;
	OwningPool = nullptr;
}

void APooledActor::PostInitProperties() {
	Super::PostInitProperties();
}

void APooledActor::BeginPlay() {
	Super::BeginPlay();
}

void APooledActor::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	OnPoolBeginPlay.Clear();
	OnPoolEndPlay.Clear();
	//
	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APooledActor::Initialize() {
	Spawned = false;
	//
	SetLifeSpan(0.f);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	//
	TInlineComponentArray<UActorComponent*>Components;
	GetComponents(Components);
	//
	for (UActorComponent* C : Components) {
		const auto &PS = Cast<UParticleSystemComponent>(C);
		if (PS) {PS->DeactivateSystem();}
		//
		C->SetActive(false);
		C->SetComponentTickEnabled(false);
		//
		const auto &P = Cast<UPrimitiveComponent>(C);
		if (P && !P->IsA(UParticleSystemComponent::StaticClass())) {
			P->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			P->SetPhysicsLinearVelocity(FVector::ZeroVector);
			P->SetComponentTickEnabled(false);
			P->SetSimulatePhysics(false);
			P->SetVisibility(false,true);
		}///
	}///
	//
	if (OwningPool && OwningPool->IsValidLowLevelFast()) {
		OwningPool->ReturnActor(const_cast<APooledActor*>(this));
	} else if (SharedPool && SharedPool->IsValidLowLevelFast()) {
		SharedPool->ReturnActor(const_cast<APooledActor*>(this));
	}///
}

void APooledActor::SetLifeSpanPool(float InLifespan) {
	if (HasAuthority() && !IsPendingKill()) {
		LifeSpanPool = InLifespan;
		//
		if (InLifespan>0.0001f) {
			GetWorldTimerManager().SetTimer(LifeSpanHandle,this,&APooledActor::ReturnToPool,InLifespan);
		} else {GetWorldTimerManager().ClearTimer(LifeSpanHandle);}
	}///
}

float APooledActor::GetLifeSpanPool() const {
	const float CurrentLifespan = GetWorldTimerManager().GetTimerRemaining(LifeSpanHandle);
	return (CurrentLifespan!=-1.0f) ? CurrentLifespan : 0.0f;
}

UObjectPool* APooledActor::GetOwningPool() const {
	return OwningPool;
}

USharedObjectPool* APooledActor::GetSharedPool() const {
	return SharedPool;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APooledActor::SpawnFromPool(const bool Reconstruct, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform) {
	if ((!OwningPool||!OwningPool->IsValidLowLevelFast())&&(!SharedPool||!SharedPool->IsValidLowLevelFast())) {
		UE_LOG(LogTemp,Warning,TEXT("{Pool}:: %s"),TEXT("Actor trying to spawn from Pool, but Owning Pool Component is invalid!"));
	return;}
	//
	Spawned = true;
	//
	//
	TInlineComponentArray<UActorComponent*>Components;
	GetComponents(Components);
	//
	for (UActorComponent* C : Components) {
		const auto &P = Cast<UPrimitiveComponent>(C);
		if (P && !P->IsA(UParticleSystemComponent::StaticClass())) {
			P->SetComponentTickEnabled(SpawnOptions.ActorTickEnabled);
			P->SetSimulatePhysics(SpawnOptions.SimulatePhysics);
			P->SetVisibility(true,true);
		}///
	}///
	//
	if ((OwningPool && OwningPool->ReinitializeInstances)||(SharedPool && SharedPool->ReinitializeInstances)) {
		SetActorLocationAndRotation(SpawnTransform.GetLocation(),SpawnTransform.GetRotation(),false,nullptr,ETeleportType::ResetPhysics);
		SetActorEnableCollision(SpawnOptions.EnableCollision);
		SetActorTickEnabled(SpawnOptions.ActorTickEnabled);
		SetActorScale3D(SpawnTransform.GetScale3D());
	}///
	//
	//
	SetActorHiddenInGame(false);
}

void APooledActor::FinishSpawnFromPool(const bool Reconstruct, const FTransform &Transform) {
	FTransform FinalRootComponentTransform = (RootComponent ? RootComponent->GetComponentTransform() : Transform);
	FinalRootComponentTransform.GetLocation().DiagnosticCheckNaN(TEXT("APooledActor::FinishSpawning: FinalRootComponentTransform.GetLocation()"));
	FinalRootComponentTransform.GetRotation().DiagnosticCheckNaN(TEXT("APooledActor::FinishSpawning: FinalRootComponentTransform.GetRotation()"));
	//
	if (GetWorld()) {
		FVector AdjustedLocation; FRotator AdjustedRotation;
		switch (SpawnCollisionHandlingMethod) {
			case ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn:
				AdjustedLocation = GetActorLocation();
				AdjustedRotation = GetActorRotation();
				if (GetWorld()->FindTeleportSpot(this,AdjustedLocation,AdjustedRotation)) {
					SetActorLocationAndRotation(AdjustedLocation,AdjustedRotation,false,nullptr,ETeleportType::TeleportPhysics);
			} break;
			//
			case ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding:	
				AdjustedLocation = GetActorLocation();
				AdjustedRotation = GetActorRotation();
				if (GetWorld()->FindTeleportSpot(this,AdjustedLocation,AdjustedRotation)) {
					SetActorLocationAndRotation(AdjustedLocation,AdjustedRotation,false,nullptr,ETeleportType::TeleportPhysics);
				} else {
					UE_LOG(LogTemp,Warning,TEXT("Spawn Actor from Pool: failed because of collision at the spawn location [%s] for [%s]"),*AdjustedLocation.ToString(),*GetClass()->GetName());
					Initialize();
				return;}
			break;
			//
			case ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding:
				if (GetWorld()->EncroachingBlockingGeometry(this,GetActorLocation(),GetActorRotation())) {
					UE_LOG(LogTemp,Warning,TEXT("Spawn Actor from Pool: failed because of collision at the spawn location [%s] for [%s]"),*GetActorLocation().ToString(),*GetClass()->GetName());
					Initialize();
				return;}
			break;
			//
			case ESpawnActorCollisionHandlingMethod::Undefined:
			case ESpawnActorCollisionHandlingMethod::AlwaysSpawn:
	default: break;}}
	//
	//
	if (Reconstruct) {
		ResetPropertiesForConstruction();
		RerunConstructionScripts();
	}///
	//
	if (LifeSpanPool>0.0001f) {
		GetWorldTimerManager().SetTimer(LifeSpanHandle,this,&APooledActor::ReturnToPool,LifeSpanPool);
	}///
	//
	//
	TInlineComponentArray<UActorComponent*>Components;
	GetComponents(Components);
	//
	for (UActorComponent* C : Components) {
		const auto &PS = Cast<UParticleSystemComponent>(C);
		if (PS) {PS->ActivateSystem(false);}
		//
		C->SetActive(true);
		C->SetComponentTickEnabled(true);
	}///
	//
	//
	EVENT_OnPoolBeginPlay();
	OnPoolBeginPlay.Broadcast();
	//
	Spawned = true;
}

void APooledActor::ReturnToPool() {
	TInlineComponentArray<UActorComponent*>Components;
	GetComponents(Components);
	//
	for (UActorComponent* C : Components) {
		const auto &PS = Cast<UParticleSystemComponent>(C);
		if (PS) {PS->DeactivateSystem();}
		//
		C->SetActive(false);
		C->SetComponentTickEnabled(false);
		//
		const auto &P = Cast<UPrimitiveComponent>(C);
		if (P && !P->IsA(UParticleSystemComponent::StaticClass())) {
			P->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			P->SetPhysicsLinearVelocity(FVector::ZeroVector);
			P->SetComponentTickEnabled(false);
			P->SetSimulatePhysics(false);
			P->SetVisibility(false,true);
		}///
	}///
	//
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	//
	if (OwningPool && OwningPool->IsValidLowLevelFast()) {
		if (OwningPool->ReinitializeInstances) {
			GetWorld()->GetTimerManager().ClearTimer(LifeSpanHandle);
		} OwningPool->ReturnActor(const_cast<APooledActor*>(this));
		//
		OnPoolEndPlay.Broadcast();
		EVENT_OnPoolEndPlay();
	} else if (SharedPool && SharedPool->IsValidLowLevelFast()) {
		if (SharedPool->ReinitializeInstances) {
			GetWorld()->GetTimerManager().ClearTimer(LifeSpanHandle);
		} SharedPool->ReturnActor(const_cast<APooledActor*>(this));
		//
		OnPoolEndPlay.Broadcast();
		EVENT_OnPoolEndPlay();
	} else {Destroy(true,true);}
	//
	Spawned = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APooledActor::EVENT_OnPoolBeginPlay_Implementation(){}
void APooledActor::EVENT_OnPoolEndPlay_Implementation(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////