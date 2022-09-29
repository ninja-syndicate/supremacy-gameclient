// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataWeapon.h"
#include "StaticDataWeaponSkin.h"
#include "StaticDataWeaponSkinCompatibility.generated.h"

namespace StaticDataImporter
{
	class WeaponSkinCompatibility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataWeaponSkinCompatibility : public UStaticDataBaseRecord
{
public:
	friend class StaticDataImporter::WeaponSkinCompatibility;
	
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataWeapon *Weapon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataWeaponSkin *WeaponSkin;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "References", meta = (AllowPrivateAccess = true))
	TMap<FString, TSoftObjectPtr<UMaterial>> Materials;
};
