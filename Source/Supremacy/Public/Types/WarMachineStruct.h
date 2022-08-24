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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="total_wins"))
	int TotalWins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="total_deaths"))
	int TotalDeaths;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="total_kills"))
	int TotalKills;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="battles_survived"))
	int BattlesSurvived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="total_losses"))
	int TotalLosses;

	FWarMachineStats(): TotalWins(0), TotalDeaths(0), TotalKills(0), BattlesSurvived(0), TotalLosses(0) {}
};

USTRUCT(BlueprintType)
struct FWarMachinePowerStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="idle_drain"))
	float IdleDrain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="walk_drain"))
	float WalkDrain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="run_drain"))
	float RunDrain;

	FWarMachinePowerStats(): IdleDrain(0), WalkDrain(0), RunDrain(0) {}
};

USTRUCT(BlueprintType)
struct FWarMachineCustomisation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="intro_animation_id"))
	FString IntroAnimationID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="outro_animation_id"))
	FString OutroAnimationID;

	FWarMachineCustomisation() {}
};

USTRUCT(BlueprintType)
struct FWarMachineStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="hash"))
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="name"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="owner_name"))
	FString OwnerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="faction"))
	FFaction Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="model"))
	FString Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="skin"))
	FString Skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="rarity"))
	ERarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="weapons"))
	TArray<FWeaponStruct> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="customisation"))
	FWarMachineCustomisation Customisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="health"))
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="health_max"))
	int HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="shield_max"))
	int ShieldMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="shield_recharge_rate"))
	float ShieldRechargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(DisplayName ="sprint_spread_modifier"))
	float SprintSpreadModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="speed"))
	int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="power_core"))
	FPowerCoreStruct PowerCore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="power_stats"))
	FWarMachinePowerStats PowerStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="stats"))
	FWarMachineStats Stats;

	FWarMachineStruct(): Rarity(ERarity::Rarity_Default), Health(3000), HealthMax(3000), ShieldMax(0), ShieldRechargeRate(0), Speed(0), SprintSpreadModifier(1.25)
	{}
};