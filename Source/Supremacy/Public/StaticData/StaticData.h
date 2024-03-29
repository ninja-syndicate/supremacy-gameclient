﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.h"
#include "StaticDataSkin.h"
#include "StaticDataWeaponSkin.h"
#include "StaticDataWeapon.h"
#include "StaticDataWarMachineModel.h"
#include "StaticDataMechSkinCompatibility.h"
#include "StaticDataPowerCore.h"
#include "StaticDataWeaponSkinCompatibility.h"
#include "StaticDataBattleAbility.h"
#include "StaticDataFactionPalette.h"
#include "StaticDataPlayerAbility.h"
#include "StaticDataGameAbility.h"
#include "StaticDataShieldType.h"
#include "Types/AbilityID.h"
#include "StaticData.generated.h"

namespace StaticDataImporter
{
	class Base;
	class Faction;
    class FactionPalette;
	class Brand;
	class WarMachineModel;
	class Skin;
	class WeaponSkin;
	class Weapon;
	class MechSkinCompatibility;
	class WeaponSkinCompatibility;
	class PowerCore;
	class BattleAbility;
	class PlayerAbility;
	class GameAbility;
    class ShieldType;
}

/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UPrimaryDataAsset
{
	friend StaticDataImporter::Base;

	GENERATED_BODY()

    friend StaticDataImporter::Faction;
    friend StaticDataImporter::FactionPalette;
    friend StaticDataImporter::Brand;
    friend StaticDataImporter::WarMachineModel;
    friend StaticDataImporter::Skin;
    friend StaticDataImporter::WeaponSkin;
    friend StaticDataImporter::Weapon;
    friend StaticDataImporter::MechSkinCompatibility;
    friend StaticDataImporter::WeaponSkinCompatibility;
    friend StaticDataImporter::PowerCore;
    friend StaticDataImporter::BattleAbility;
    friend StaticDataImporter::PlayerAbility;
    friend StaticDataImporter::GameAbility;
    friend StaticDataImporter::ShieldType;

public:
    UFUNCTION(BlueprintCallable)
    UStaticDataFaction* GetFaction(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    UStaticDataFactionPalette* GetFactionPalette(const FGuid& ID);

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

    UStaticDataMechSkinCompatibility* GetMechSkinCompatibility(const FGuid& ID);
    UFUNCTION(BlueprintCallable)
    UStaticDataMechSkinCompatibility* GetMechSkinCompatibility(const FGuid& MechID, const FGuid& SkinID);

    UStaticDataWeaponSkinCompatibility* GetWeaponSkinCompatibility(const FGuid& ID);
    UFUNCTION(BlueprintCallable)
    UStaticDataWeaponSkinCompatibility* GetWeaponSkinCompatibility(const FGuid& WeaponID, const FGuid& SkinID);

    UFUNCTION(BlueprintCallable)
    UStaticDataPowerCore* GetPowerCore(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    TArray<UStaticDataPowerCore*> GetPowerCoresBySize(const EWarMachinePowerCoreSize& Size);

    UFUNCTION(BlueprintCallable)
    UStaticDataBattleAbility* GetBattleAbility(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    UStaticDataPlayerAbility* GetPlayerAbility(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    UStaticDataPlayerAbility* GetPlayerAbilityByGameClientAbilityID(const EAbilityID& ID);

    UFUNCTION(BlueprintCallable)
    UStaticDataGameAbility* GetGameAbility(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    UStaticDataGameAbility* GetGameAbilityByGameClientAbilityID(const EAbilityID& ID, const FGuid& FactionID);

    UFUNCTION(BlueprintCallable)
    UStaticDataShieldType* GetShieldType(const FGuid& ID);

    UFUNCTION(BlueprintCallable)
    FPowerCoreStruct PowerCoreStruct(const FGuid& PowerCoreID);

    UFUNCTION(BlueprintCallable)
    TMap<FString, TSoftObjectPtr<UMaterial>> MaterialsForMech(const FGuid &MechID, const FGuid& SkinID);

    UFUNCTION(BlueprintCallable)
    TMap<FString, TSoftObjectPtr<UMaterial>> MaterialsForWeapon(const FGuid& WeaponID, const FGuid& SkinID);

    UFUNCTION(BlueprintCallable, meta=(ToolTip="Get an array of all possible skins for a mech model."))
    TArray<UStaticDataSkin*> GetMechSkins(const FGuid& MechModelID);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mech Abilities")
    float GetAbilityCooldown(const EAbilityID Ability);
    
    UFUNCTION(BlueprintCallable)
    void Clear();

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataFaction*> FactionArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataFactionPalette*> FactionPaletteArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataBrand*> BrandArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataWarMachineModel*> WarMachineModelArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataSkin*> SkinArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataWeaponSkin*> WeaponSkinArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataWeapon*> WeaponArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataMechSkinCompatibility*> MechSkinCompatibilityArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataWeaponSkinCompatibility*> WeaponSkinCompatibilityArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataPowerCore*> PowerCoreArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataBattleAbility*> BattleAbilityArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataPlayerAbility*> PlayerAbilityArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataGameAbility*> GameAbilityArray;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess))
        TArray<UStaticDataShieldType*> ShieldTypeArray;

private:
    UStaticDataFaction* GetOrCreateFaction(const FGuid& ID);
    UStaticDataFactionPalette* GetOrCreateFactionPalette(const FGuid& ID);
    UStaticDataBrand* GetOrCreateBrand(const FGuid& ID);
    UStaticDataWarMachineModel* GetOrCreateWarMachineModel(const FGuid& ID);
    UStaticDataSkin* GetOrCreateSkin(const FGuid& ID);
    UStaticDataWeaponSkin* GetOrCreateWeaponSkin(const FGuid& ID);
    UStaticDataWeapon* GetOrCreateWeapon(const FGuid& ID);
    UStaticDataMechSkinCompatibility* GetOrCreateMechSkinCompatibility(const FGuid& ID);
    UStaticDataWeaponSkinCompatibility* GetOrCreateWeaponSkinCompatibility(const FGuid& ID);
    UStaticDataPowerCore* GetOrCreatePowerCore(const FGuid& ID);
    UStaticDataBattleAbility* GetOrCreateBattleAbility(const FGuid& ID);
    UStaticDataPlayerAbility* GetOrCreatePlayerAbility(const FGuid& ID);
    UStaticDataGameAbility* GetOrCreateGameAbility(const FGuid& ID);
    UStaticDataShieldType* GetOrCreateShieldType(const FGuid& ID);
};
