#include "Weapons/WeaponBarrel.h"
#include "EBBullet.h"

UWeaponBarrel::UWeaponBarrel()
{
	PrimaryComponentTick.bCanEverTick = true;
	bHiddenInGame = true;
	bAutoActivate = true;
	SetIsReplicatedByDefault(ReplicateVariables);

	RandomStream.GenerateNewSeed();
}

void UWeaponBarrel::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ClientSideAim)
	{
		if (GetOwner()->GetRemoteRole() == ROLE_Authority)
		{
			TimeSinceAimUpdate += DeltaTime;

			if (TimeSinceAimUpdate >= 1.0f / ClientAimUpdateFrequency)
			{
				Aim = GetComponentTransform().GetUnitAxis(EAxis::X);
				Location = GetComponentTransform().GetLocation();
				ClientAim(UGameplayStatics::RebaseLocalOriginOntoZero(GetWorld(), Location), Aim);
				TimeSinceAimUpdate = FMath::Fmod(TimeSinceAimUpdate, 1.0f / ClientAimUpdateFrequency);
			};
		}
		else
		{
			if (!RemoteAimReceived)
			{
				Aim = GetComponentTransform().GetUnitAxis(EAxis::X);
				Location = GetComponentTransform().GetLocation();
			}
			else
			{
				if (const FVector LocOffset = (Location - GetComponentLocation()); LocOffset.Size() >
					ClientAimDistanceLimit)
				{
					//lag or cheater???
					Location = GetComponentLocation() + LocOffset.GetSafeNormal() * ClientAimDistanceLimit;
				}
			}
		}
	}
	else
	{
		Aim = GetComponentTransform().GetUnitAxis(EAxis::X);
		Location = GetComponentTransform().GetLocation();
	}

	//Only server can tick
	if (GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		float RemainingDelta = DeltaTime;

		do
		{
			const float Step = FMath::Min(Cooldown, RemainingDelta);

			Cooldown -= Step;

			RemainingDelta -= Step;

			//shoot when ready
			if (Shooting && (!ShootingBlocked) && Cooldown <= 0)
			{
				if (ProjectileAmount > 0 && BurstFireRate == 0)
				{
					// Shotgun
					for (int i = 0; i < ProjectileAmount; i++)
					{
						SpawnBullet(Location, Aim);
					}
				}
				else
				{
					SpawnBullet(Location, Aim);
				}
			}
		}
		while (RemainingDelta > 0 && Cooldown > 0);
	}
}

void UWeaponBarrel::SpawnBullet(const FVector InLocation, const FVector InDirection)
{
	if (!Ammo) return;
	
	FVector OutLocation;
	FVector OutAim;

	InitialBulletTransform(InLocation, InDirection, OutLocation, OutAim);

	const AEBBullet* Default = Cast<AEBBullet>(Ammo->GetDefaultObject());

	OutAim = RandomStream.VRandCone(OutAim, Spread + Default->Spread);
	FVector Velocity = OutAim * MuzzleVelocityMultiplier;

	//get parent physics body
	UPrimitiveComponent* Parent = Cast<UPrimitiveComponent>(GetAttachParent());
	Velocity += AdditionalVelocity;

	if (Parent != nullptr)
	{
		if (Parent->IsSimulatingPhysics())
		{
			Velocity += Parent->GetPhysicsLinearVelocityAtPoint(OutLocation) * InheritVelocity;
		}

		ApplyRecoil(Parent, OutLocation, -Velocity * Default->Mass * RecoilMultiplier);
	}
	
	//UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, LocalLocation, )

	BeforeShotFired.Broadcast();

	AActor* Owner = GetOwner();
	AEBBullet::SpawnWithExactVelocity(Ammo, Owner, Owner->GetInstigator(), OutLocation, Velocity);

	Cooldown = 60.0f / FireRate;
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Cooldown: %f"), Cooldown));
	
	if (ReplicateShotFiredEvents)
	{
		ShotFiredMulticast();
	}
	else
	{
		ShotFired.Broadcast();
	}
}

void UWeaponBarrel::SpawnBulletFromBarrel()
{
	SpawnBullet(GetComponentTransform().GetLocation(), GetComponentTransform().GetUnitAxis(EAxis::X));
}

void UWeaponBarrel::InitialBulletTransform_Implementation(const FVector InLocation, const FVector InDirection, FVector& OutLocation,
                                                          FVector& OutDirection)
{
	OutLocation = InLocation;
	OutDirection = InDirection;
}

void UWeaponBarrel::ApplyRecoil_Implementation(UPrimitiveComponent* Component, const FVector InLocation, const FVector Impulse)
{
	if (Component->IsSimulatingPhysics())
	{
		Component->AddImpulseAtLocation(Impulse, InLocation);
	}
}

void UWeaponBarrel::CalculateAimDirection(TSubclassOf<class AEBBullet> BulletClass, FVector TargetLocation,
                                          FVector TargetVelocity, FVector& AimDirection,
                                          FVector& PredictedTargetLocation, FVector& PredictedIntersectionLocation,
                                          float& PredictedFlightTime, float& Error, float MaxTime, float Step,
                                          int NumIterations) const
{
	const FVector StartLocation = GetComponentLocation();
	CalculateAimDirectionFromLocation(BulletClass, StartLocation, TargetLocation, TargetVelocity, AimDirection,
	                                  PredictedTargetLocation, PredictedIntersectionLocation, PredictedFlightTime,
	                                  Error, MaxTime, Step, NumIterations);
}

void UWeaponBarrel::CalculateAimDirectionFromLocation(TSubclassOf<class AEBBullet> BulletClass, FVector StartLocation,
                                                      FVector TargetLocation, FVector TargetVelocity,
                                                      FVector& AimDirection, FVector& PredictedTargetLocation,
                                                      FVector& PredictedIntersectionLocation,
                                                      float& PredictedFlightTime, float& Error, float MaxTime,
                                                      float Step, int NumIterations) const
{
	if (!BulletClass->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("CalculateAimDirection - invalid bullet class"));
		return;
	}

	AEBBullet* Bullet = Cast<AEBBullet>(BulletClass->GetDefaultObject());

	FVector AddVelocity = AdditionalVelocity;
	if (UPrimitiveComponent* Parent = Cast<UPrimitiveComponent>(GetAttachParent()); Parent != nullptr)
	{
		if (Parent->IsSimulatingPhysics())
		{
			AddVelocity += Parent->GetPhysicsLinearVelocityAtPoint(StartLocation) * InheritVelocity;
		}
	}


	FVector InitialAimDirection = (TargetLocation - StartLocation).GetSafeNormal(); //initial prediction
	AimDirection = InitialAimDirection;

	for (int Iteration = 0; Iteration < NumIterations; Iteration++)
	{
		FVector CurrentBulletLocation = StartLocation;
		FVector Velocity = (AimDirection * (MuzzleVelocityMultiplier * FMath::Lerp(
			Bullet->MuzzleVelocityMin, Bullet->MuzzleVelocityMax, 0.5))) + AddVelocity;
		bool bHit = false;
		for (float Time = 0; Time <= MaxTime; Time += Step)
		{
			FVector PreviousVelocity = Velocity;
			Velocity = Bullet->UpdateVelocity(GetWorld(), CurrentBulletLocation, Velocity, Step);

			FVector TraceVector = ((((PreviousVelocity + Velocity) * 0.5) - TargetVelocity) * Step);
			FVector TraceEndLocation = CurrentBulletLocation + TraceVector;
			FVector IntersectionPoint;

			bHit = FMath::SegmentPlaneIntersection(CurrentBulletLocation - TraceVector, TraceEndLocation,
			                                       FPlane(TargetLocation, InitialAimDirection), IntersectionPoint);
			//actual hit test

			if (bHit)
			{
				PredictedIntersectionLocation = IntersectionPoint;
				FQuat AimCorrection = FQuat::FindBetween((IntersectionPoint - StartLocation),
				                                         (TargetLocation - StartLocation));
				AimDirection = AimCorrection.RotateVector(AimDirection).GetSafeNormal();
				Error = (IntersectionPoint - TargetLocation).Size();

				float AdditionalFlightTime = (FVector(CurrentBulletLocation - IntersectionPoint).Size() / TraceVector.
					Size()) * Step;
				PredictedFlightTime = Time + AdditionalFlightTime;
				PredictedTargetLocation = TargetLocation + TargetVelocity * AdditionalFlightTime;

				break;
			}

			//no hit, keep going
			CurrentBulletLocation = TraceEndLocation;
		}
		if (!bHit)
		{
			Error = 99999999999999999.0f;
			return; //no solution
		}
	}
}
