// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataBattleAbility.generated.h"

namespace StaticDataImporter
{
	class BattleAbility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataBattleAbility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::BattleAbility;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 Cooldown;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Description;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString KillingPowerLevel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 MaximumCommanderCount;
};
