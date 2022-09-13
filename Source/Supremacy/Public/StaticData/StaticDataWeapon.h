// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "StaticDataBrand.h"
#include "UObject/Object.h"
#include "StaticDataWeapon.generated.h"

namespace StaticDataImporter
{
	class Skin;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataSkin : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::Skin;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Type;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataSkin* DefaultSkin;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBrand* Brand;
};
