// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptAgentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UScriptAgentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPREMACY_API IScriptAgentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// @todo - match parameter
	// @todo - test whether javascript to interface call works.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Script API")
	bool TriggerWeapon(int SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Script API")
	bool ReleaseWeapon(int SlotIndex);

	// @todo- accept movement mode enum argument.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Script API")
	bool SetMovementMode();
};
