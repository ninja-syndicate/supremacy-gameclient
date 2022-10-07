#pragma once

#include "CoreMinimal.h"
#include "Faction.h"
#include "PowerCoreStruct.h"
#include "Rarity.h"
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
	FFactionServer Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin;
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
	int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Sprint_Spread_Modifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPowerCoreStruct Power_Core;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachinePowerStats Power_Stats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineStats Stats;

	FWarMachineServerStruct(): Height(0), Health(3000), Health_Max(3000), Shield_Max(0), Shield_Recharge_Rate(0), Speed(0), Sprint_Spread_Modifier(1.25)
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
	FFaction Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ModelID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin;
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
	int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSpreadModifier;

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
		Faction(WarMachine.Faction),
		Model(WarMachine.Model),
		ModelID(WarMachine.Model_ID),
		Skin(WarMachine.Skin),
		SkinID(WarMachine.Skin_ID),
		Rarity(StringToERarity[WarMachine.Tier]),

		Weapons(WarMachine.Weapons),
		Customisation(WarMachine.Customisation),
	
		Height(WarMachine.Height),

		Health(WarMachine.Health),
		HealthMax(WarMachine.Health_Max),
		ShieldMax(WarMachine.Shield_Max),
		ShieldRechargeRate(WarMachine.Shield_Recharge_Rate),
	
		Speed(WarMachine.Speed),
		SprintSpreadModifier(WarMachine.Sprint_Spread_Modifier),

		PowerCore(WarMachine.Power_Core),
		PowerStats(WarMachine.Power_Stats),

		Stats(WarMachine.Stats)
	{}

	FWarMachineStruct(): Rarity(ERarity::Rarity_Default), Height(0), Health(3000), HealthMax(3000), ShieldMax(0), ShieldRechargeRate(0), Speed(0), SprintSpreadModifier(1.25)
	{}
};