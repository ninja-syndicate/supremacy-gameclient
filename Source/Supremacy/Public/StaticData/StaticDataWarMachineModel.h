﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "StaticDataBrand.h"
#include "Mechs/Mech.h"
#include "Types/ShieldType.h"
#include "Types/WarMachineBoostStat.h"
#include "Types/WarMachineType.h"
#include "Types/WarMachinePowerCoreSize.h"
#include "StaticDataWarMachineModel.generated.h"

namespace StaticDataImporter
{
	class WarMachineModel;
}

class UStaticDataSkin;

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataWarMachineModel : public UStaticDataBaseRecord
{
public:
	friend class StaticDataImporter::WarMachineModel;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWarMachineModelType Type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWarMachineBoostStat BoostStat;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 WeaponHardpointCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 UtilitySlotCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 MaxHitpoints;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 Speed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float WalkSpeedModifier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWarMachinePowerCoreSize PowerCoreSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Collection;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
    FString CreatedAt;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float MaxShield;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float ShieldRechargeRate;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float ShieldRechargePowerCost;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FGuid ShieldTypeId;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EShieldType ShieldType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float ShieldRechargeDelay;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float Height;

	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float SprintSpreadModifier;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float IdleDrain;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float WalkDrain;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	float RunDrain;
	
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	UStaticDataSkin *DefaultSkin;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBrand *Brand;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="References", meta=(AllowPrivateAccess=true))
	TSoftClassPtr<AMech> UnrealWarMachine;

	UFUNCTION(BlueprintPure, meta=(DisplayName="To WarMachineStruct (From StaticDataWarMachine)", CompactNodeTitle = "->", BlueprintAutocast))
	FWarMachineStruct ToWarMachineStruct() const
	{
		FWarMachineStruct Struct;

		Struct.Name = Label;
		Struct.Faction = Brand->Faction->ToFaction();

		//ERarity Rarity;

		Struct.ModelID = ID.ToString(EGuidFormats::DigitsWithHyphens).ToLower();
		Struct.ModelName = Label;
		Struct.Health = MaxHitpoints;
		Struct.HealthMax = MaxHitpoints;
		Struct.ShieldMax = MaxShield;
		Struct.ShieldRechargeRate = ShieldRechargeRate;
		Struct.Speed = Speed;
		Struct.WalkSpeedModifier = WalkSpeedModifier;
		Struct.Height = Height;

		Struct.ShieldType = ShieldType;
		Struct.PowerStats.Idle_Drain = IdleDrain;
		Struct.PowerStats.Walk_Drain = WalkDrain;
		Struct.PowerStats.Run_Drain = RunDrain;

		// if (DefaultSkin)
		// {
		// 	Struct.SkinID = DefaultSkin->ID.ToString(EGuidFormats::DigitsWithHyphens).ToLower();
		// 	Struct.SkinName = DefaultSkin->Label;
		// }
		
		return Struct;
	}
	
};
