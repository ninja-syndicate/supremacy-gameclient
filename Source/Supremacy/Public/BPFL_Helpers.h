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

	/** Parses  */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Parse Net Message", meta=(Keywords = "Parse Net Message Bytes Byte Array"))
	static void ParseNetMessage(const TArray<uint8> Bytes, uint8 &Type, FString &Message);

	/** Pack WarMachine Move Update  */
	UFUNCTION(BlueprintPure, Category = "Network", DisplayName = "Pack WarMachine Move Update", meta=(Keywords = "Net Message Bytes Byte Array Binary"))
	static void PackWarMachineMoveUpdate(const uint8 Number, const FVector Location, const float Yaw, TArray<uint8> &Bytes);
	
	/** Converts a String to an Array of bytes */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Convert String To Bytes")
	static void ConvertStringToBytes(const FString String, TArray<uint8> &Bytes);
	
	/** Converts an Array of bytes to a String */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Convert Bytes To String")
	static void ConvertBytesToString(const TArray<uint8> Bytes, FString &String);
	
	/** Converts hex string to color. Supports formats RGB, RRGGBB, RRGGBBAA, RGB, #RRGGBB, #RRGGBBAA */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Helpers")
    static FColor HexToColor(const FString HexString);
    
    /** Converts color to hex string */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Helpers")
    static FString ColorToHex(const FColor Color);
};
