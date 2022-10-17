// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "Types/WarMachinePowerCoreSize.h"
#include "Types/PowerCoreStruct.h"
#include "StaticDataPowerCore.generated.h"

namespace StaticDataImporter
{
	class PowerCore;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataPowerCore : public UStaticDataBaseRecord
{
public:
	friend class StaticDataImporter::PowerCore;
	
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Collection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	EWarMachinePowerCoreSize Size;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float Capacity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float MaxDrawRate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float RechargeRate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float Armour;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	float MaxHitpoints;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Tier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString CreatedAt;

	UFUNCTION(BlueprintPure, meta=(DisplayName="To PowerCoreStruct (From StaticDataPowerCore)", CompactNodeTitle = "->", BlueprintAutocast))
	FPowerCoreStruct ToPowerCoreStruct() const
	{
		FPowerCoreStruct Struct;
		Struct.ID = ID.ToString();
		Struct.Power_Capacity = Capacity;
		Struct.Recharge_Rate = RechargeRate;
		Struct.Max_Draw_Rate = MaxDrawRate;
		
		return Struct;
	}
};
