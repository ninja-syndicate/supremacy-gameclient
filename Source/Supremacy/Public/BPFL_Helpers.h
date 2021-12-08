// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_Helpers.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UBPFL_Helpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Converts a String to an Array of bytes */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Convert String To Bytes")
	static void ConvertStringToBytes(const FString String, TArray<uint8> &Bytes);
};
