// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataPlayerAbility.generated.h"

namespace StaticDataImporter
{
	class PlayerAbility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataPlayerAbility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::PlayerAbility;
	
	GENERATED_BODY()
};
