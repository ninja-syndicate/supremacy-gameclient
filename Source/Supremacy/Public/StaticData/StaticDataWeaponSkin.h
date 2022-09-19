// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataWeaponSkin.generated.h"

namespace StaticDataImporter
{
	class WeaponSkin;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataWeaponSkin : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::WeaponSkin;
	
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Collection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Tier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString CreatedAt;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 StatModifier;
};
