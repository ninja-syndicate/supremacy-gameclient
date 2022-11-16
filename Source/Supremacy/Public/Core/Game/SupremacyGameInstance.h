// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SupremacyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API USupremacyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USupremacyGameInstance();

protected:
	// @note - WIP DO NOT USE ANYTHING.
	UPROPERTY(Category = "Supremacy Game Instance", EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UDamageType>> DamageTypes;
};
