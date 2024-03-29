#pragma once

#include "CoreMinimal.h"
#include "Faction.h"
#include "PowerCoreStruct.h"
#include "Rarity.h"
#include "ShieldType.h"
#include "WeaponStruct.h"
#include "WarMachineStruct.generated.h"

USTRUCT(BlueprintType)
struct FWarMachineStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Total_Wins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Total_Deaths;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Total_Kills;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Battles_Survived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Total_Losses;

	FWarMachineStats(): Total_Wins(0), Total_Deaths(0), Total_Kills(0), Battles_Survived(0), Total_Losses(0) {}
};

USTRUCT(BlueprintType)
struct FWarMachinePowerStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Idle_Drain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Walk_Drain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Run_Drain;

	FWarMachinePowerStats(): Idle_Drain(0), Walk_Drain(0), Run_Drain(0) {}
};

USTRUCT(BlueprintType)
struct FWarMachineCustomisation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString IntroAnimationID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OutroAnimationID;

	FWarMachineCustomisation() {}
	FWarMachineCustomisation(FString IntroAnimationID, FString OutroAnimationID)
	{
		this->IntroAnimationID = IntroAnimationID;
		this->OutroAnimationID = OutroAnimationID;
	}
};

USTRUCT(BlueprintType, meta=(ToolTip="Same as FWarMachineStruct but for incoming war machines from the server."))
struct FWarMachineServerStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Owner_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Owner_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFactionServer Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponStruct> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineCustomisation Customisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health_Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Shield_Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Shield_Recharge_Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Shield_Recharge_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Shield_Type_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Walk_Speed_Modifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Sprint_Spread_Modifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Melee_Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPowerCoreStruct Power_Core;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachinePowerStats Power_Stats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineStats Stats;

	FWarMachineServerStruct(): Height(0), Health(3000), Health_Max(3000), Shield_Max(0), Shield_Recharge_Rate(0),
	                           Shield_Recharge_Delay(0), Speed(0), Walk_Speed_Modifier(2), Sprint_Spread_Modifier(1.25),
	                           Melee_Force(20)
	{}
};

class AMech;

USTRUCT(BlueprintType)
struct FWarMachineStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OwnerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OwnerID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFaction Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ModelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ModelID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkinName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkinID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponStruct> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineCustomisation Customisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShieldMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShieldRechargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShieldRechargeDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ShieldTypeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeedModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSpreadModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MeleeForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EShieldType ShieldType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPowerCoreStruct PowerCore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachinePowerStats PowerStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineStats Stats;
	
	// Convert From Server Struct
	explicit FWarMachineStruct(const FWarMachineServerStruct& WarMachine) :
		Hash(WarMachine.Hash),
		Name(WarMachine.Name),
		OwnerName(WarMachine.Owner_Name),
		OwnerID(WarMachine.Owner_ID),
		Faction(WarMachine.Faction),
		ModelName(WarMachine.Model_Name),
		ModelID(WarMachine.Model_ID),
		SkinName(WarMachine.Skin_Name),
		SkinID(WarMachine.Skin_ID),
		Rarity(StringToERarity[WarMachine.Tier]),

		Weapons(WarMachine.Weapons),
		Customisation(WarMachine.Customisation),

		Height(WarMachine.Height),

		Health(WarMachine.Health),
		HealthMax(WarMachine.Health_Max),
		ShieldMax(WarMachine.Shield_Max),
		ShieldRechargeRate(WarMachine.Shield_Recharge_Rate),
		ShieldRechargeDelay(WarMachine.Shield_Recharge_Delay),
		ShieldTypeID(WarMachine.Shield_Type_ID),

		Speed(WarMachine.Speed),
		WalkSpeedModifier(WarMachine.Walk_Speed_Modifier),
		SprintSpreadModifier(WarMachine.Sprint_Spread_Modifier),

		MeleeForce(WarMachine.Melee_Force),

		ShieldType(EShieldType::ShieldType_Orb),
		PowerCore(WarMachine.Power_Core),
		PowerStats(WarMachine.Power_Stats),

		Stats(WarMachine.Stats)
	{
		// Sort weapons by socket index
		const auto SortWeaponBySlotPredicate = [](const FWeaponStruct& ThisWeapon, const FWeaponStruct& OtherWeapon)
		{
			return ThisWeapon.Socket_Index < OtherWeapon.Socket_Index;
		};
		Weapons.Sort(SortWeaponBySlotPredicate);

		// Get Shield Type
		if (FGuid ShieldTypeGuid; FGuid::Parse(WarMachine.Shield_Type_ID, ShieldTypeGuid))
			ShieldType = GuidToEShieldType[ShieldTypeGuid];
	}

	FWarMachineStruct(): Rarity(ERarity::Rarity_Default), Height(0), Health(3000), HealthMax(3000), ShieldMax(0),
	                     ShieldRechargeRate(0), ShieldRechargeDelay(0), Speed(0), WalkSpeedModifier(2),
	                     SprintSpreadModifier(1.25), MeleeForce(20), ShieldType(EShieldType::ShieldType_Orb)
	{}
};