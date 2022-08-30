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

	// Only server can tick
	if (GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		bool ShouldShoot = false;
		
		// Charging
		if (Charging && !Shooting && ChargeCancellable)
			Charging = false;
		if (Charging)
		{
			CurrentCharge += DeltaTime;
			if (CurrentCharge >= ChargeTime)
			{
				CurrentCharge = ChargeTime;
				Charging = false;
				ChargeCompletedMulticast();
				if (!ChargeCancellable)
					ShouldShoot = true;
			}
		}
		else if (ChargeCancellable && CurrentCharge > 0 && !Shooting)
		{
			CurrentCharge = FMath::Max(CurrentCharge - DeltaTime, 0);
		}

		if (!Charging)
		{
			float RemainingDelta = DeltaTime;
			do
			{
				const float Step = FMath::Min(Cooldown, RemainingDelta);
				
				if (!ShouldShoot) ShouldShoot = Shooting;
			
				// Burst Gap
				if (BurstCooldown > 0)
				{
					BurstCooldown -= Step;
					if (BurstCooldown <= 0)
						BurstCount = 0;
				}

				// Fire Gap
				if (BurstCooldown <= 0)
					Cooldown -= Step;
			
				RemainingDelta -= Step;

				// Shoot while in burst
				if (!ShouldShoot)
					ShouldShoot = BurstFireRate > 0 && BurstCooldown <= 0 && BurstCount > 0 && BurstCount < ProjectileAmount;

				// Shoot
				if (ShouldShoot && (!ShootingBlocked) && Cooldown <= 0)
				{
					if (ChargeTime > 0 && !Charging && CurrentCharge < ChargeTime)
					{
						// Start Charging
						Charging = true;
						ChargeStartedMulticast();
						RemainingDelta = 0;
					}
					else
					{
						SpawnBullet(Location, Aim);

						// Burst fire?
						if (BurstFireRate > 0)
						{
							BurstCount++;
							if (BurstCount >= ProjectileAmount)
								BurstCooldown = 60.0f / FireRate;
						}
					}
				}
			}
			while (RemainingDelta > 0 && Cooldown > 0);
		}
	}
}

void UWeaponBarrel::SpawnBullet(const FVector InLocation, const FVector InDirection)
{
	if (!BulletClass) return;

	FVector OutLocation;
	FVector OutAim;

	InitialBulletTransform(InLocation, InDirection, OutLocation, OutAim);

	const AEBBullet* Default = Cast<AEBBullet>(BulletClass->GetDefaultObject());

	FVector Velocity = RandomStream.VRandCone(OutAim, Spread + Default->Spread) * MuzzleVelocityMultiplier + AdditionalVelocity;

	// get parent physics body
	if (UPrimitiveComponent* Parent = Cast<UPrimitiveComponent>(GetAttachParent()); Parent != nullptr)
	{
		if (Parent->IsSimulatingPhysics())
		{
			Velocity += Parent->GetPhysicsLinearVelocityAtPoint(OutLocation) * InheritVelocity;
		}

		ApplyRecoil(Parent, OutLocation, -Velocity * Default->Mass * RecoilMultiplier);
	}

	BeforeShotFired.Broadcast();

	AActor* Owner = GetOwner();

	// Arc
	if (IsArced)
	{
		const FVector EndPos = UKismetMathLibrary::RandomPointInBoundingBox(CurrentTargetLocation, FVector(Spread));
		UGameplayStatics::SuggestProjectileVelocity_CustomArc(
			GetWorld(),
			Velocity,
			OutLocation,
			EndPos,
			Default->Gravity.Z, ArcParam
		);
	}

	// Spawn Projectiles
	if (ProjectileAmount > 0 && BurstFireRate == 0)
	{
		// Shotgun
		for (int i = 0; i < ProjectileAmount; i++)
		{
			AEBBullet::SpawnWithExactVelocity(BulletClass, Owner, Owner->GetInstigator(), OutLocation, Velocity);

			Velocity = RandomStream.VRandCone(OutAim, Spread + Default->Spread) * MuzzleVelocityMultiplier + AdditionalVelocity;
		}
	}
	else
	{
		AEBBullet::SpawnWithExactVelocity(BulletClass, Owner, Owner->GetInstigator(), OutLocation, Velocity);
	}

	// Cooldown (if burst fire, BurstFireRate is used otherwise FireRate)
	if (BurstFireRate > 0)
	{
		Cooldown = 60.0f / BurstFireRate;
	}
	else
	{
		Cooldown = 60.0f / FireRate;
	}

	if (ChargeEachShot) CurrentCharge = 0;

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

void UWeaponBarrel::InitialBulletTransform_Implementation(const FVector InLocation, const FVector InDirection,
                                                          FVector& OutLocation,
                                                          FVector& OutDirection)
{
	OutLocation = InLocation;
	OutDirection = InDirection;
}

void UWeaponBarrel::ApplyRecoil_Implementation(UPrimitiveComponent* Component, const FVector InLocation,
                                               const FVector Impulse)
{
	if (Component->IsSimulatingPhysics())
	{
		Component->AddImpulseAtLocation(Impulse, InLocation);
	}
}

void UWeaponBarrel::CalculateAimDirection(FVector TargetLocation,
                                          FVector TargetVelocity, FVector& AimDirection,
                                          FVector& PredictedTargetLocation, FVector& PredictedIntersectionLocation,
                                          float& PredictedFlightTime, float& Error, float MaxTime, float Step,
                                          int NumIterations) const
{
	const FVector StartLocation = GetComponentLocation();
	CalculateAimDirectionFromLocation(StartLocation, TargetLocation, TargetVelocity, AimDirection,
	                                  PredictedTargetLocation, PredictedIntersectionLocation, PredictedFlightTime,
	                                  Error, MaxTime, Step, NumIterations);
}

void UWeaponBarrel::CalculateAimDirectionFromLocation(FVector StartLocation,
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
