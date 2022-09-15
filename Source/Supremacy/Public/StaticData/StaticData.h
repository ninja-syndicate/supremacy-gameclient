// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.h"
#include "StaticDataSkin.h"
#include "StaticDataWeaponSkin.h"
#include "StaticDataWeapon.h"
#include "StaticDataWarMachineModel.h"
#include "StaticDataMechSkinCompatibility.h"
#include "StaticDataWeaponSkinCompatibility.h"
#include "StaticData.generated.h"

namespace StaticDataImporter
{
	class Base;
	class Faction;
	class Brand;
	class WarMachineModel;
	class Skin;
	class Weapon;
	class MechSkinCompatibility;
	class WeaponSkinCompatibility;
}

/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UPrimaryDataAsset
{
	friend StaticDataImporter::Base;
	friend StaticDataImporter::Faction;
	friend StaticDataImporter::Brand;
	friend StaticDataImporter::WarMachineModel;
	friend StaticDataImporter::Skin;
	friend StaticDataImporter::Weapon;
	friend StaticDataImporter::WeaponSkin;
	friend StaticDataImporter::MechSkinCompatibility;
	friend StaticDataImporter::WeaponSkinCompatibility;
	
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UStaticDataFaction* GetFaction(const FGuid &ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataBrand* GetBrand(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataWarMachineModel* GetWarMachineModel(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataSkin* GetSkin(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataWeaponSkin* GetWeaponSkin(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataWeapon* GetWeapon(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataMechSkinCompatibility* GetMechSkinCompatibility(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataWeaponSkinCompatibility* GetWeaponSkinCompatibility(const FGuid& ID);
private:
	UStaticDataFaction* GetOrCreateFaction(const FGuid &ID);
	UStaticDataBrand* GetOrCreateBrand(const FGuid& ID);
	UStaticDataWarMachineModel* GetOrCreateWarMachineModel(const FGuid& ID);
	UStaticDataSkin* GetOrCreateSkin(const FGuid& ID);
	UStaticDataWeaponSkin* GetOrCreateWeaponSkin(const FGuid& ID);
	UStaticDataWeapon* GetOrCreateWeapon(const FGuid& ID);
	UStaticDataMechSkinCompatibility *GetOrCreateMechSkinCompatibility(const FGuid& ID);
	UStaticDataWeaponSkinCompatibility *GetOrCreateWeaponSkinCompatibility(const FGuid& ID);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataFaction*> Factions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataBrand*> Brands;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataWarMachineModel*> WarMachineModels;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataSkin*> Skins;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataWeaponSkin*> WeaponSkins;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataWeapon*> Weapons;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataMechSkinCompatibility*> MechSkinCompatibilities;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataWeaponSkinCompatibility*> WeaponSkinCompatibilities;
};
