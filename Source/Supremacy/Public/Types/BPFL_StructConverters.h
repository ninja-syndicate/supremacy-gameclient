#pragma once

#include "CoreMinimal.h"
#include "DamageHistory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Network/BattleCommand.h"
#include "Types/WarMachineStruct.h"
#include "BPFL_StructConverters.generated.h"

UCLASS()
class SUPREMACY_API UBPFL_StructConverters final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="To WarMachineStruct (From WarMachineServerStruct)", CompactNodeTitle = "->", BlueprintAutocast))
	static FWarMachineStruct Conv_WarMachineServerStructToWarMachineStruct(const FWarMachineServerStruct& WarMachine)
	{
		return FWarMachineStruct(WarMachine);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To Faction (From FactionServer)", CompactNodeTitle = "->", BlueprintAutocast))
	static FFaction Conv_FactionServerToFaction(const FFactionServer& FactionServer)
	{
		return FFaction(FactionServer);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To ERarity (From String)", CompactNodeTitle = "->", BlueprintAutocast))
	static ERarity Conv_StringToERarity(const FString& RarityString)
	{
		return StringToERarity[RarityString];
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To DamageHistoryResultItem (From DamageHistoryItem)", CompactNodeTitle = "->", BlueprintAutocast))
	static FDamageHistoryResultItem Conv_DamageHistoryItemToDamageHistoryResultItem(const FDamageHistoryItem& DamageHistoryItem)
	{
		return FDamageHistoryResultItem(DamageHistoryItem);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To String (From BattleCommand)", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_BattleCommandToString(const EBattleCommand& BattleCommand)
	{
		return BattleCommandToString[BattleCommand];
	}
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set WarMachineStruct Defaults", ToolTip="Fills empty variables with values from DefaultStruct. For use with StaticData and struct sent from game server, in-case server doesn't send everything."))
	static void SetWarMachineStructDefaults(UPARAM(ref) FWarMachineStruct& Struct, const FWarMachineStruct& DefaultStruct)
	{
		if (Struct.Health == 0) Struct.Health = DefaultStruct.Health;
		if (Struct.HealthMax == 0) Struct.HealthMax = DefaultStruct.HealthMax;
		if (Struct.ShieldMax == 0) Struct.ShieldMax = DefaultStruct.ShieldMax;
		if (Struct.ShieldRechargeRate == 0) Struct.ShieldRechargeRate = DefaultStruct.ShieldRechargeRate;
		if (Struct.Speed == 0) Struct.Speed = DefaultStruct.Speed;
		if (Struct.SprintSpreadModifier == 0) Struct.SprintSpreadModifier = DefaultStruct.SprintSpreadModifier;
		if (Struct.Height == 0) Struct.Height = DefaultStruct.Height;
	}

	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set WeaponStruct Defaults", ToolTip="Fills empty variables with values from DefaultStruct. For use with StaticData and struct sent from game server, in-case server doesn't send everything."))
	static void SetWeaponStructDefaults(UPARAM(ref) FWeaponStruct& Struct, const FWeaponStruct& DefaultStruct)
	{
		if (Struct.Damage == 0) Struct.Damage = DefaultStruct.Damage;
		if (Struct.Damage_Falloff == 0) Struct.Damage_Falloff = DefaultStruct.Damage_Falloff;
		if (Struct.Damage_Falloff_Rate == 0) Struct.Damage_Falloff_Rate = DefaultStruct.Damage_Falloff_Rate;
		if (Struct.Damage_Radius == 0) Struct.Damage_Radius = DefaultStruct.Damage_Radius;
		if (Struct.Damage_Radius_Falloff == 0) Struct.Damage_Radius_Falloff = DefaultStruct.Damage_Radius_Falloff;
		if (Struct.Damage_Type == 0) Struct.Damage_Type = DefaultStruct.Damage_Type;
		if (Struct.Spread == 0) Struct.Spread = DefaultStruct.Spread;
		if (Struct.Rate_Of_Fire == 0) Struct.Rate_Of_Fire = DefaultStruct.Rate_Of_Fire;
		if (Struct.Burst_Rate_Of_Fire == 0) Struct.Burst_Rate_Of_Fire = DefaultStruct.Burst_Rate_Of_Fire;
		if (Struct.Projectile_Speed == 0) Struct.Projectile_Speed = DefaultStruct.Projectile_Speed;
		if (Struct.Max_Ammo == 0) Struct.Max_Ammo = DefaultStruct.Max_Ammo;
		if (Struct.Projectile_Amount == 0) Struct.Projectile_Amount = DefaultStruct.Projectile_Amount;
		if (Struct.Projectile_Life_Span == 0) Struct.Projectile_Life_Span = DefaultStruct.Projectile_Life_Span;
		if (Struct.Charge_Time == 0) Struct.Charge_Time = DefaultStruct.Charge_Time;
		if (Struct.Recoil_Force == 0) Struct.Recoil_Force = DefaultStruct.Recoil_Force;
		if (Struct.Power_Cost == 0) Struct.Power_Cost = DefaultStruct.Power_Cost;
		if (Struct.Power_Instance_Drain == 0) Struct.Power_Instance_Drain = DefaultStruct.Power_Instance_Drain;
	}
};
