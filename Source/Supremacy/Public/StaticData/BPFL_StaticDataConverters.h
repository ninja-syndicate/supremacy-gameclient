#pragma once

#include "StaticData/StaticDataWeapon.h"
#include "StaticData/StaticDataWarMachineModel.h"
#include "Types/WarMachineStruct.h"
#include "BPFL_StaticDataConverters.generated.h"

UCLASS()
class SUPREMACY_API UBPFL_StaticDataConverters final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, meta=(DisplayName="To Faction (From StaticDataFaction)", CompactNodeTitle = "->", BlueprintAutocast))
	static FFaction Conv_StaticDataFactionToFaction(const UStaticDataFaction* Record)
	{
		FFaction Struct;
		Struct.ID = Record->ID.ToString();
		Struct.Name = Record->Label;
		Struct.Color = Record->PrimaryColor;
		
		return Struct;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="To WarMachineStruct (From StaticDataWarMachine)", CompactNodeTitle = "->", BlueprintAutocast))
    static FWarMachineStruct Conv_StaticDataWarMachineToWarMachineStruct(const UStaticDataWarMachineModel* Record)
    {
    	FWarMachineStruct Struct;
        if (!Record) {
            return Struct;
        }

	    Struct.Name = Record->Label;
	    Struct.Faction = Conv_StaticDataFactionToFaction(Record->Brand->Faction);

	    //ERarity Rarity;

	    Struct.Health = Record->MaxHitpoints;
	    Struct.HealthMax = Record->MaxHitpoints;
	    Struct.ShieldMax = Record->MaxShield;
	    Struct.ShieldRechargeRate = Record->ShieldRechargeRate;
	    Struct.Speed = Record->Speed;
	    Struct.Height = Record->Height;
		
    	return Struct;
    }
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="To WeaponStruct (From StaticDataWeapon)", CompactNodeTitle = "->", BlueprintAutocast))
	static FWeaponStruct Conv_StaticDataWeaponToWeaponStruct(const UStaticDataWeapon* Record)
	{
		FWeaponStruct Struct;
		if (!Record) {
			return Struct;
		}

		Struct.Damage = Record->Damage;
		Struct.Damage_Falloff = Record->DamageFalloff;
		Struct.Damage_Falloff_Rate = Record->DamageFalloffRate;
		Struct.Damage_Radius = Record->Radius;
		Struct.Damage_Radius_Falloff = Record->RadiusDamageFalloff;
		Struct.Damage_Type = static_cast<uint8>(Record->WeaponDamageType);
		Struct.Spread = Record->Spread;
		Struct.Rate_Of_Fire = Record->RateOfFire;
		Struct.Burst_Rate_Of_Fire = Record->BurstRateOfFire;
		Struct.Projectile_Speed = Record->ProjectileSpeed;
		Struct.Max_Ammo = Record->MaxAmmo;
		Struct.Projectile_Amount = Record->ProjectileAmount;
		//Struct.Projectile_Life_Span = ...;
		Struct.Charge_Time = Record->ChargeTimeSeconds;
		Struct.Is_Arced = Record->IsArced;
		//Struct.Optimal_Range = ...;
		//Struct.Recoil_Force = ...;
		Struct.Power_Cost = Record->EnergyCost;
		Struct.Power_Instance_Drain = Record->PowerInstantDrain;

		return Struct;
	}
};
