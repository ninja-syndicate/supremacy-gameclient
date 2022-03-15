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

	/** Pack WarMachine Update  */
	UFUNCTION(BlueprintPure, Category = "Network", DisplayName = "Pack WarMachine Update", meta=(Keywords = "Net Message Bytes Byte Array Binary"))
	static void PackWarMachineUpdate(const uint8 Number, const int X, const int Y, const int Yaw, const int Health, const int Shield, const uint8 SyncByte, TArray<uint8> &Bytes);
	
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

	/**
	 * Get a nearest empty location around the origin.
	 *
	 * @param WorldContextObject World context which is automatically binded if called from blueprint.
	 * @param Origin The starting location to search for the nearest empty location.
	 * @param ForwardAxis The forward direction.
	 * @param UpAxis The up direction.
	 * @param DesiredRadius The minimum desired radius of empty location. Usually, this is actor radius.
	 * @param MaxDistance The maximum distance to consider to search for the empty location.
	 * @param bCheckGround If true, the empty location will be on ground. Otherwise, it may be mid-air.
	 * @param OutLocation The nearest empty location around the origin.
	 *	
	 * @return Returns true when such an empty location is found and false otherwise.
	 *
	 * @note This function can be pretty expensive. So, don't call it every frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Helpers", meta = (WorldContext = "WorldContextObject"))
	static bool GetNearestEmptyLocation(
		const UObject* WorldContextObject, 
		FVector Origin, 
		FVector ForwardAxis, 
		FVector UpAxis, 
		float DesiredRadius, 
		float MaxDistance,
		TArray<AActor*> ActorsToIgnore,
		FVector& OutLocation,
		bool bCheckGround = true);
};
