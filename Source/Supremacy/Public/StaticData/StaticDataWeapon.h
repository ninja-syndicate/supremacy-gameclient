// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "StaticDataBrand.h"
#include "UObject/Object.h"
#include "Weapons/Weapon.h"
#include "Types/WeaponType.h"
#include "Types/WeaponDamageType.h"
#include "StaticDataWeapon.generated.h"

namespace StaticDataImporter
{
	class Weapon;
}

class UStaticDataWeaponSkin;
class UStaticDataBrand;

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataWeapon : public UStaticDataBaseRecord
{
public:
	friend class StaticDataImporter::Weapon;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWeaponType Type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float Damage;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float DamageFalloff;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float DamageFalloffRate;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float Radius;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float RadiusDamageFalloff;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float Spread;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float RateOfFire;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float ProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float MaxAmmo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool IsMelee;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float EnergyCost;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FGuid GameClientWeaponID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Collection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWeaponDamageType WeaponDamageType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float ProjectileAmount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float DotTickDamage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float DotMaxTicks;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool IsArced;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float ChargeTimeSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float BurstRateOfFire;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool PowerInstantDrain;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataWeaponSkin* DefaultSkin;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBrand* Brand;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "References", meta = (AllowPrivateAccess = true))
	TSoftClassPtr<AWeapon> Blueprint;

	UFUNCTION(BlueprintPure, meta=(DisplayName="To WeaponStruct (From StaticDataWeapon)", CompactNodeTitle = "->", BlueprintAutocast))
	FWeaponStruct ToWeaponStruct()
	{
		FWeaponStruct Struct;

		Struct.Model_ID = ID.ToString();
		Struct.Model_Name = Label;
		Struct.Damage = Damage;
		Struct.Damage_Falloff = DamageFalloff;
		Struct.Damage_Falloff_Rate = DamageFalloffRate;
		Struct.Damage_Radius = Radius;
		Struct.Damage_Radius_Falloff = RadiusDamageFalloff;
		Struct.Damage_Type = static_cast<uint8>(WeaponDamageType);
		Struct.Spread = Spread;
		Struct.Rate_Of_Fire = RateOfFire;
		Struct.Burst_Rate_Of_Fire = BurstRateOfFire;
		Struct.Projectile_Speed = ProjectileSpeed;
		Struct.Max_Ammo = MaxAmmo;
		Struct.Projectile_Amount = ProjectileAmount;
		//Struct.Projectile_Life_Span = ...;
		Struct.Charge_Time = ChargeTimeSeconds;
		Struct.Is_Arced = IsArced;
		//Struct.Optimal_Range = ...;
		//Struct.Recoil_Force = ...;
		Struct.Power_Cost = EnergyCost;
		Struct.Power_Instance_Drain = PowerInstantDrain;

		return Struct;
	}
};
