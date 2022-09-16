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

	
};
