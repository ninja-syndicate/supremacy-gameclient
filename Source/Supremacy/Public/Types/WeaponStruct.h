#pragma once

#include "CoreMinimal.h"
#include "WeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="id", ToolTip="UUID that client uses to apply weapon stats to the correct weapons (unique per model/blueprint)"))
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="hash", ToolTip="Unique hash of a user's weapon"))
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="name"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="model"))
	FString Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="skin"))
	FString Skin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage"))
	int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage_falloff", ToolTip="Distance at which damage starts decreasing"))
	int DamageFalloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage_falloff_rate", ToolTip="How much the damage decreases by per km"))
	int DamageFalloffRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage_radius", ToolTip="Enemies within this radius when the projectile hits something is damaged"))
	int DamageRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage_radius_falloff", ToolTip="Distance at which damage starts decreasing (must be greater than 0 and less than damageRadius to have any affect)"))
	int DamageRadiusFalloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="damage_type"))
	uint8 DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="spread", ToolTip="Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees."))
	float Spread;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="rate_of_fire", ToolTip="Rounds per minute"))
	float RateOfFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="burst_rate_of_fire", ToolTip="Rounds per minute within the burst of fire (rateOfFire is used for the time between bursts))"))
	float BurstRateOfFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="projectile_speed", ToolTip="cm/s"))
	int ProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="max_ammo", ToolTip="The max amount of ammo this weapon can hold"))
	int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="projectile_amount", ToolTip="The amount of projectile spawned per shot or burst."))
	int ProjectileAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="charge_time", ToolTip="Time before weapon starts firing (eg: minigun spin-up)"))
	float ChargeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="is_arced", ToolTip="Arcs projectiles towards their target location. Spread becomes radius offset."))
	bool IsArced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="power_cost"))
	float PowerCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="power_instant_drain"))
	bool PowerInstantDrain;
	
	FWeaponStruct(): Damage(0), DamageFalloff(0), DamageFalloffRate(0), DamageRadius(0), DamageRadiusFalloff(0),
	                 DamageType(0),
	                 Spread(0),
	                 RateOfFire(0),
	                 BurstRateOfFire(0),
	                 ProjectileSpeed(0), MaxAmmo(0),
	                 ProjectileAmount(0),
	                 ChargeTime(0),
	                 IsArced(false),
	                 PowerCost(0), PowerInstantDrain(false)
	{}
};
