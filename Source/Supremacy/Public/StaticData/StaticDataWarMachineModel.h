// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "StaticDataBrand.h"
#include "Mechs/Mech.h"
#include "Types/WarMachineBoostStat.h"
#include "Types/WarMachineType.h"
#include "Types/WarMachinePowerCoreSize.h"
#include "UObject/Object.h"
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
	
	// TOOD: Shield Type
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	// ShieldTypeId;
	
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	UStaticDataSkin *DefaultSkin;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBrand *Brand;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="References", meta=(AllowPrivateAccess=true))
	TSoftClassPtr<AMech> UnrealWarMachine;
};
