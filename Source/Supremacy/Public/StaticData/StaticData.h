// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataFaction.h"
#include "StaticData.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UStaticData : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	TArray<FStaticDataFaction> Factions;
};
