// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticData.generated.h"


/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//WARNING: do _not_ call these functions from gameplay code. These are here to make the importer work.
	FStaticDataFaction GetOrCreateFaction(FGuid &id);
	void UpdateFaction(const FStaticDataFaction& Record);

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<FStaticDataFaction> Factions;
};
