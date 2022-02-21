//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PooledSplineProjectile.h"
#include "OBJPool_Shared.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UPooledSplineProjectile::UPooledSplineProjectile() {
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	SetComponentTickEnabled(true);
	//
	PathDistance = 0.f;
	PathWidth = 10.f;
	Speed = 2.f;
	//
	IgnoredActorsOnCollisionQuery = TArray<AActor*>();
	CollisionQueryDebugMode = EDrawDebugTrace::ForDuration;
	PathCollisionQueryTypes = TArray<TEnumAsByte<EObjectTypeQuery>>();
	//
	PathCollisionQueryTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	PathCollisionQueryTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
}

void UPooledSplineProjectile::PostInitProperties() {
	Super::PostInitProperties();
	//
	AOwner = Cast<APooledActor>(GetOwner());
	POwner = Cast<APooledPawn>(GetOwner());
	//
	if ((!AOwner)&&(!POwner)) {return;}
	//
	if (AOwner) {
		AOwner->OnPoolEndPlay.AddDynamic(this,&UPooledSplineProjectile::Break);
		AOwner->OnPoolBeginPlay.AddDynamic(this,&UPooledSplineProjectile::Shoot);
	} else if (POwner) {
		POwner->OnPoolEndPlay.AddDynamic(this,&UPooledSplineProjectile::Break);
		POwner->OnPoolBeginPlay.AddDynamic(this,&UPooledSplineProjectile::Shoot);
	}///
	//
	if (!Primitive) {
		AOwner = Cast<APooledActor>(GetOwner());
		POwner = Cast<APooledPawn>(GetOwner());
		//
		if (AOwner) {Primitive=Cast<UPrimitiveComponent>(AOwner->GetRootComponent());} else
		if (POwner) {Primitive=Cast<UPrimitiveComponent>(POwner->GetRootComponent());}
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UPooledSplineProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	if (!SplineComponent||!Primitive) {return;}
	//
	//
	PathDistance += (DeltaTime * Speed);
	float SplineLength = SplineComponent->GetSplineLength();
	float PathLocation = FMath::Lerp<float>(0.f,SplineLength,PathDistance);
	//
	FRotator SplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(PathLocation,ESplineCoordinateSpace::World);
	FVector SplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(PathLocation,ESplineCoordinateSpace::World);
	Primitive->SetWorldLocationAndRotation(SplineLocation,SplineRotation);
	//
	{///
		const FVector TraceStart = SplineLocation;
		const FVector TraceEnd = SplineLocation + FVector(KINDA_SMALL_NUMBER,KINDA_SMALL_NUMBER,KINDA_SMALL_NUMBER);
		//
		const bool Hit = UKismetSystemLibrary::SphereTraceSingleForObjects(
			Primitive,
			TraceStart,
			TraceEnd,
			PathWidth,
			PathCollisionQueryTypes,
			true,
			IgnoredActorsOnCollisionQuery,
			CollisionQueryDebugMode,
			HitResult,
			true,
			FLinearColor::Yellow,
			FLinearColor::Green,
			1.f
		);//
		//
		if (Hit) {
			OnProjectileHit.Broadcast(HitResult);
			SetComponentTickEnabled(false);
			//
			if (AOwner) {AOwner->ReturnToPool();} else
			if (POwner) {POwner->ReturnToPool();}
		}///
	}///
	//
	if (PathLocation >= SplineLength) {
		if (AOwner) {AOwner->ReturnToPool();} else
		if (POwner) {POwner->ReturnToPool();}
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UPooledSplineProjectile::Shoot_Implementation() {
	if (!SplineComponent) {
		UE_LOG(LogTemp,Error,TEXT("{Pool}:: %s"),TEXT("Pooled Spline Projectile Components need a target Spline Component to follow. Spline path not found!"));
	return;}
	//
	if (!Primitive) {
		UE_LOG(LogTemp,Error,TEXT("{Pool}:: %s"),TEXT("Pooled Spline Projectile Components need a parent Primitive Component as root. Root Component not found!"));
	return;}
	//
	PathDistance = 0.f;
	SetComponentTickEnabled(true);
}

void UPooledSplineProjectile::Break_Implementation() {
	SetComponentTickEnabled(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

USplineComponent* UPooledSplineProjectile::GetSplineComponent() const {
	return SplineComponent;
}

void UPooledSplineProjectile::SetSplineComponent(USplineComponent* Target) {
	SplineComponent = Target;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////