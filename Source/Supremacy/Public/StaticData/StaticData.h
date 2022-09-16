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
#include "StaticDataPowerCore.h"
#include "StaticDataWeaponSkinCompatibility.h"
#include "StaticDataBattleAbility.h"
#include "StaticData.generated.h"

namespace StaticDataImporter
{
	class Base;
}

/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UPrimaryDataAsset
{
	friend StaticDataImporter::Base;
	
	GENERATED_BODY()

	#define STATIC_DATA_STUFF_HEADER(n) \
		friend StaticDataImporter::n; \
		public: \
			UFUNCTION(BlueprintCallable) \
			UStaticData##n* Get##n(const FGuid& ID); \
		private: UStaticData##n* GetOrCreate##n(const FGuid& ID); TArray<UStaticData##n*> n##Array;
	
	STATIC_DATA_STUFF_HEADER(Faction);
	STATIC_DATA_STUFF_HEADER(Brand);
	STATIC_DATA_STUFF_HEADER(WarMachineModel);
	STATIC_DATA_STUFF_HEADER(Skin);
	STATIC_DATA_STUFF_HEADER(WeaponSkin);
	STATIC_DATA_STUFF_HEADER(Weapon);
	STATIC_DATA_STUFF_HEADER(MechSkinCompatibility);
	STATIC_DATA_STUFF_HEADER(WeaponSkinCompatibility);
	STATIC_DATA_STUFF_HEADER(PowerCore);
	STATIC_DATA_STUFF_HEADER(BattleAbility);
};
