﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.h"
#include "StaticDataWarMachineModel.h"
#include "StaticData.generated.h"

namespace StaticDataImporter
{
	class Base;
	class Faction;
	class Brand;
	class WarMachineModel;
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
	
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UStaticDataFaction* GetFaction(const FGuid &ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataBrand* GetBrand(const FGuid& ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataWarMachineModel* GetWarMachineModel(const FGuid& ID);
	
private:
	UStaticDataFaction* GetOrCreateFaction(const FGuid &ID);
	UStaticDataBrand* GetOrCreateBrand(const FGuid& ID);
	UStaticDataWarMachineModel* GetOrCreateWarMachineModel(const FGuid& ID);
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataFaction*> Factions;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataBrand*> Brands;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, EditFixedSize, meta=(AllowPrivateAccess))
	TArray<UStaticDataWarMachineModel*> WarMachineModels;
};
