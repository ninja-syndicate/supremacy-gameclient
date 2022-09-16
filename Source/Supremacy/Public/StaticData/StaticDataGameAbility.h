// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataGameAbility.generated.h"

namespace StaticDataImporter
{
	class GameAbility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataGameAbility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::GameAbility;
	
	GENERATED_BODY()
};
