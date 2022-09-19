// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataShieldType.generated.h"

namespace StaticDataImporter
{
	class ShieldType;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataShieldType : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::ShieldType;

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString Description;
};
