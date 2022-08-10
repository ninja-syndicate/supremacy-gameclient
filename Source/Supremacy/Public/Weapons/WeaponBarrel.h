#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "WeaponBarrel.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), hidecategories = (Object, LOD, Physics, Lighting, TextureStreaming, Collision, HLOD, Mobile, VirtualTexture, ComponentReplication), editinlinenew, meta = (BlueprintSpawnableComponent))
	class SUPREMACY_API UWeaponBarrel final : public UPrimitiveComponent
{

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponBarrel();

	// Called every frame
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") float DebugArrowSize = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Bullet inherits barrel velocity, only works with physics enabled or with additional velocity set")) float InheritVelocity = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Amount of recoil applied to the barrel, only works with physics enabled")) float RecoilMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Additional velocity, for use with InheritVelocity")) FVector AdditionalVelocity = FVector(0,0,0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Additional Spread, applied on top of bullet spread. Half-angle of cone, in radians. If IsArced Spread is the half size of bounding box at CurrentTargetLocation.", ClampMin = "0")) float Spread=0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Multiplier applied to bullet muzzle velocity")) float MuzzleVelocityMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Fire rate, rounds per minute")) float FireRate = 60.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Fire rate inside a burst, rounds per minute. 0 = Non-burst weapon.")) float BurstFireRate = 0.0f;
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon") bool ShootingBlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arced Firing", meta = (ToolTip = "If true; projectiles will arc towards CurrentTargetLocation.")) bool IsArced = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arced Firing", meta = (ToolTip = "Optional override of WorldGravityZ for calculating arc. If 0; will use projectile's gravity.")) float ArcOverrideGravityZ = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arced Firing", meta = (ToolTip = "Change height of arc between 0.0-1.0 where 0.5 is the default medium arc, 0 is up, and 1 is directly toward CurrentTargetLocation.")) float ArcParam = 0.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arced Firing", meta = (ToolTip = "World location that projectile will land at when arcing.")) FVector CurrentTargetLocation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Number of projectiles spawned per shot")) int ProjectileAmount = 1;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Ammo") TSubclassOf<class AEBBullet> BulletClass;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "WeaponState") bool Shooting;
	
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState") float Cooldown;
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState") float BurstCooldown;
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState") int BurstCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication") bool ReplicateVariables=true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication") bool ReplicateShotFiredEvents = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication") bool ClientSideAim=false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication") float ClientAimUpdateFrequency = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication") float ClientAimDistanceLimit = 200.0f;

	FRandomStream RandomStream;

	UFUNCTION(BlueprintCallable, Category = "Shooting") void Shoot(const bool Trigger);
	UFUNCTION(BlueprintCallable, Category = "Shooting", meta=(ToolTip="Manually spawn a bullet at location with direction.")) void SpawnBullet(const FVector InLocation, const FVector InDirection);
	UFUNCTION(BlueprintCallable, Category = "Shooting", meta=(ToolTip="Manually spawn a bullet from the barrel.")) void SpawnBulletFromBarrel();

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "IgnoredActors"), Category = "Prediction") void PredictHit(bool& Hit, FHitResult& HitResult, FVector& HitLocation, float& HitTime, AActor*& HitActor, TArray<FVector>& Trajectory, const TArray<AActor*>IgnoredActors, const float MaxTime = 10.0f, const float Step = 0.1f) const;
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "IgnoredActors"), Category = "Prediction") void PredictHitFromLocation(bool &Hit, FHitResult& TraceResult, FVector& HitLocation, float& HitTime, AActor*& HitActor, TArray<FVector>& Trajectory, const FVector StartLocation, const FVector AimDirection, const TArray<AActor*>IgnoredActors, const float MaxTime = 10.0f, const float Step = 0.1f) const;
	UFUNCTION(BlueprintCallable, Category = "Prediction") void CalculateAimDirection(FVector TargetLocation, FVector TargetVelocity, FVector& AimDirection, FVector& PredictedTargetLocation, FVector& PredictedIntersectionLocation, float& PredictedFlightTime, float& Error, float MaxTime = 10.0f, float Step = 0.1f, int NumIterations = 4) const;
	UFUNCTION(BlueprintCallable, Category = "Prediction") void CalculateAimDirectionFromLocation(FVector StartLocation, FVector TargetLocation, FVector TargetVelocity, FVector& AimDirection, FVector& PredictedTargetLocation, FVector& PredictedIntersectionLocation, float& PredictedFlightTime, float& Error, float MaxTime = 10.0f, float Step=0.1f, int NumIterations = 4) const;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Events") void InitialBulletTransform(const FVector InLocation, const FVector InDirection, FVector& OutLocation, FVector& OutDirection);
	UFUNCTION(BlueprintNativeEvent, Category = "Events") void ApplyRecoil(UPrimitiveComponent* Component, const FVector InLocation, const FVector Impulse);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeforeShotFired);
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FBeforeShotFired BeforeShotFired;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShotFired);
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FShotFired ShotFired;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAmmoDepleted);
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FAmmoDepleted AmmoDepleted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReadyToShoot);
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FReadyToShoot ReadyToShoot;

#ifdef WITH_EDITOR
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
#endif

private:
	UFUNCTION(Server, Unreliable, WithValidation) void ClientAim(const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim);
	UFUNCTION(Server, Reliable, WithValidation) void ShootRep(const bool Trigger);
	UFUNCTION(Server, Reliable, WithValidation) void ShootRepCSA(const bool Trigger, const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim);

	UFUNCTION(NetMulticast, Reliable)
		void ShotFiredMulticast();

	FVector Aim;
	FVector Location;
	bool RemoteAimReceived;
	float TimeSinceAimUpdate;
	bool PredictTrace(UWorld* World, AEBBullet* Bullet, FVector Start, FVector End, FHitResult &HitResult, TArray<AActor*> IgnoredActors) const;
};