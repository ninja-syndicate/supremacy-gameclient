#include "Weapons/WeaponBarrel.h"
#include "EBBullet.h"

void UWeaponBarrel::PredictHit(bool& Hit, FHitResult& HitResult, FVector& HitLocation, float& HitTime, AActor*& HitActor, TArray<FVector>& Trajectory, const TArray<AActor*> IgnoredActors, const float MaxTime, const float Step) const {
	const FVector StartLocation = GetComponentLocation();
	const FVector AimDirection = GetComponentQuat().GetForwardVector();
	PredictHitFromLocation(Hit, HitResult, HitLocation, HitTime, HitActor, Trajectory, StartLocation, AimDirection, IgnoredActors, MaxTime, Step);
}

void UWeaponBarrel::PredictHitFromLocation(bool &Hit, FHitResult& HitResult, FVector& HitLocation, float& HitTime, AActor*& HitActor, TArray<FVector>& Trajectory, const FVector StartLocation, const FVector AimDirection, const TArray<AActor*> IgnoredActors, const float MaxTime, const float Step) const{
	if (!BulletClass->IsValidLowLevel()) {
		UE_LOG(LogTemp, Warning, TEXT("PredictHit - invalid bullet class"));
		return;
	}

	float Time = 0;
	Trajectory = TArray<FVector>();

	FVector CurrentLocation = StartLocation;
	AEBBullet* Bullet = Cast<AEBBullet>(BulletClass->GetDefaultObject());
	FVector Velocity = AimDirection.GetSafeNormal()*(MuzzleVelocityMultiplier*FMath::Lerp(Bullet->MuzzleVelocityMin, Bullet->MuzzleVelocityMax, 0.5));

	UPrimitiveComponent* Parent = Cast<UPrimitiveComponent>(GetAttachParent());

	Velocity += AdditionalVelocity;

	if (Parent != nullptr) {
		if (Parent->IsSimulatingPhysics()) {
			Velocity += Parent->GetPhysicsLinearVelocityAtPoint(CurrentLocation)*InheritVelocity;
		}
	}

	while (Time < MaxTime) {
		FVector PreviousVelocity = Velocity;
		Velocity = Bullet->UpdateVelocity(GetWorld(), CurrentLocation, Velocity, Step);
		Hit = UWeaponBarrel::PredictTrace(GetWorld(), Bullet, CurrentLocation, CurrentLocation + FMath::Lerp(PreviousVelocity, Velocity, 0.5f)*Step, HitResult, IgnoredActors);
		if (Hit) {
			Trajectory.Add(HitResult.Location);
			HitTime = Time+(HitResult.Time*Step);
			HitActor = HitResult.GetActor();
			HitLocation = HitResult.Location;
			return;
		}
		else {
			Trajectory.Add(CurrentLocation);
			CurrentLocation += FMath::Lerp(PreviousVelocity, Velocity, 0.5f)*Step;
			Time += Step;
		}
	}

	Hit = false;
	HitTime = MaxTime;
	HitLocation = CurrentLocation;
	HitActor = nullptr;
}

bool UWeaponBarrel::PredictTrace(UWorld* World, AEBBullet* Bullet, FVector Start, FVector End, FHitResult &HitResult, TArray<AActor*> IgnoredActors)  const {

	FCollisionResponseParams ResponseParams;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = Bullet->TraceComplex;
	QueryParams.bReturnPhysicalMaterial = true;

	if (Bullet->SafeLaunch) {
		QueryParams.AddIgnoredActor(GetOwner());
	}

	QueryParams.AddIgnoredActors(IgnoredActors);
		
	return World->LineTraceSingleByChannel(HitResult, Start, End, Bullet->TraceChannel, QueryParams, ResponseParams);
}