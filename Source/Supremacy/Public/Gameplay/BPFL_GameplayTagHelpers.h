// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_GameplayTagHelpers.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UBPFL_GameplayTagHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Returns all tags inside the GameplayTagContainer including its parent hierarchy tags.
	 */
	UFUNCTION(BlueprintPure, Category="Gameplay Tag Helpers")
	static FGameplayTagContainer GetAllTags(const FGameplayTagContainer& GameplayTagContainer);
};
