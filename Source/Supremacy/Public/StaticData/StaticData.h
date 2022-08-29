// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.h"
#include "StaticData.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UStaticDataFaction* GetFaction(const FGuid &ID);

	UFUNCTION(BlueprintCallable)
	UStaticDataBrand* GetBrand(const FGuid& ID);

	//WARNING: do _not_ call these functions from gameplay code. These are here to make the importer work.
	UStaticDataFaction* GetOrCreateFaction(const FGuid &ID);
	UStaticDataBrand* GetOrCreateBrand(const FGuid& ID);
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<UStaticDataFaction*> Factions;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, EditFixedSize, meta=(AllowPrivateAccess))
	TArray<UStaticDataBrand*> Brands;
};
