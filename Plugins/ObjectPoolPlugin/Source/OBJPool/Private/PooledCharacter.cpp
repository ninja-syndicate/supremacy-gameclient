//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2017 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PooledCharacter.h"
#include "OBJPool_Shared.h"

#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledCharacter::APooledCharacter(const FObjectInitializer &OBJ) : Super(OBJ) {
	LifeSpanPool = 0.f;
}

void APooledCharacter::Initialize() {
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
		OwningPool->ReturnActor(const_cast<APooledCharacter*>(this));
	}///
}

void APooledCharacter::SetLifeSpanPool(float InLifespan) {
	if (!IsPendingKill()) {
		LifeSpanPool = InLifespan;
		//
		if (InLifespan>0.0001f) {
			GetWorldTimerManager().SetTimer(LifeSpanHandle,this,&APooledCharacter::ReturnToPool,InLifespan);
		} else {GetWorldTimerManager().ClearTimer(LifeSpanHandle);}
	}///
}

float APooledCharacter::GetLifeSpanPool() const {
	const float CurrentLifespan = GetWorldTimerManager().GetTimerRemaining(LifeSpanHandle);
	return (CurrentLifespan!=-1.0f) ? CurrentLifespan : 0.0f;
}

void APooledCharacter::BeginPlay() {
	Super::BeginPlay();
}

void APooledCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	OnPoolBeginPlay.Clear();
	OnPoolEndPlay.Clear();
	//
	Super::EndPlay(EndPlayReason);
}

void APooledCharacter::SpawnFromPool(const bool Reconstruct, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform) {
	if (!OwningPool||!OwningPool->IsValidLowLevelFast()) {
		UE_LOG(LogTemp,Warning,TEXT("{Pool}:: %s"),TEXT("Character trying to spawn from Pool, but Owning Pool Component is invalid!"));
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
	if (OwningPool->ReinitializeInstances) {
		SetActorLocationAndRotation(SpawnTransform.GetLocation(),SpawnTransform.GetRotation(),false,nullptr,ETeleportType::TeleportPhysics);
		SetActorEnableCollision(SpawnOptions.EnableCollision);
		SetActorTickEnabled(SpawnOptions.ActorTickEnabled);
		SetActorScale3D(SpawnTransform.GetScale3D());
		//
		FinishSpawnFromPool(Reconstruct,SpawnTransform);
		if (!Spawned) {return;}
		//
		if (LifeSpanPool>0.0001f) {
			GetWorldTimerManager().SetTimer(LifeSpanHandle,this,&APooledCharacter::ReturnToPool,LifeSpanPool);
		}///
	}///
	//
	SetActorHiddenInGame(false);
}

void APooledCharacter::FinishSpawnFromPool(const bool Reconstruct, const FTransform &Transform) {
	FTransform FinalRootComponentTransform = (RootComponent ? RootComponent->GetComponentTransform() : Transform);
	//
	FinalRootComponentTransform.GetLocation().DiagnosticCheckNaN(TEXT("APooledCharacter::FinishSpawning: FinalRootComponentTransform.GetLocation()"));
	FinalRootComponentTransform.GetRotation().DiagnosticCheckNaN(TEXT("APooledCharacter::FinishSpawning: FinalRootComponentTransform.GetRotation()"));
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
	if (Reconstruct) {
		ResetPropertiesForConstruction();
		RerunConstructionScripts();
	Reset();}
	//
	if (LifeSpanPool>0.0001f) {
		GetWorldTimerManager().SetTimer(LifeSpanHandle,this,&APooledCharacter::ReturnToPool,LifeSpanPool);
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
	}///
	//
	//
	EVENT_OnPoolBeginPlay();
	OnPoolBeginPlay.Broadcast();
	//
	Spawned = true;
}

void APooledCharacter::ReturnToPool() {
	Spawned = false;
	//
	TInlineComponentArray<UActorComponent*>Components;
	GetComponents(Components);
	//
	for (UActorComponent* C : Components) {
		const auto &PS = Cast<UParticleSystemComponent>(C);
		if (PS) {PS->DeactivateSystem();}
		//
		C->SetActive(false);
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
		} OwningPool->ReturnActor(const_cast<APooledCharacter*>(this));
		//
		OnPoolEndPlay.Broadcast();
		EVENT_OnPoolEndPlay();
	} else {Destroy();}
}

UCharacterPool* APooledCharacter::GetOwningPool() const {
	return OwningPool;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APooledCharacter::EVENT_OnPoolBeginPlay_Implementation(){}
void APooledCharacter::EVENT_OnPoolEndPlay_Implementation(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////