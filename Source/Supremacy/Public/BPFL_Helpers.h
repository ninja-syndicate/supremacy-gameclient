// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDetails.h"
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
	static void PackWarMachineUpdate(const uint8 Number, const int X, const int Y, const int Yaw, const int Health, const int Shield, const int Energy, const TArray<bool> DiffArray, TArray<uint8> &Bytes);
	
	/** Converts a String to an Array of bytes */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Convert String To Bytes")
	static void ConvertStringToBytes(const FString String, TArray<uint8> &Bytes);
	
	/** Converts an Array of bytes to a String */
	UFUNCTION(BlueprintPure, Category = "Helpers", DisplayName = "Convert Bytes To String")
	static void ConvertBytesToString(const TArray<uint8> Bytes, FString &String);

	/** Packs an array of booleans into a single byte */
	UFUNCTION(BlueprintPure, Category = "Helpers")
	static uint8 PackBooleansIntoByte(const TArray<bool> Booleans);

	/** Unpacks an array of booleans from a single byte */
	UFUNCTION(BlueprintPure, Category = "Helpers")
	static TArray<bool> UnpackBooleansFromByte(const uint8 Byte);
	
	/** Converts hex string to color. Supports formats RGB, RRGGBB, RRGGBBAA, RGB, #RRGGBB, #RRGGBBAA */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Helpers")
	static FColor HexToColor(const FString HexString);
	
	/** Converts color to hex string */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Helpers")
	static FString ColorToHex(const FColor Color);

	/** Blueprint does not have GetComponentsCollisionResponseToChannel on Actor yet. So expose that for now. */
	UFUNCTION(BLueprintCallable, Category = "Helpers")
	static ECollisionResponse GetComponentsCollisionResponseToChannel(AActor* Actor, ECollisionChannel Channel);

	/** Returns a map's details */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Helpers")
	static FMapDetails GetSupremacyMapDetails(const FString MapName, bool &IsValid)
	{
		if (!SupremacyMapDetails.Contains(MapName)) return {};
		IsValid = true;
		return *SupremacyMapDetails.Find(MapName);
	}
	
	UFUNCTION(BlueprintCallable, Category = "Helpers")
    static FString CopyMapDetailsToClipboard(const FMapDetails MapDetails);

	UFUNCTION(BlueprintCallable, Category = "Text")
	static FString GetTextFromClipboard();
	
	UFUNCTION(BlueprintCallable, Category = "Text")
	static FString ReadTextFile(const FString FilePath);
	
	/**
	 * Unreal does not expose bAllowAnyoneDestroyMe boolean variable to blueprints yet to allow
	 * actor component to be destroyed by non-owning actor. This function can be used to destroy
	 * actor component without being owning actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Helpers")
    static void ForceDestroyComponent(UActorComponent* ActorComponent);
    
	UFUNCTION(BlueprintCallable, Category = "Helpers")
    static void SetLockPhysiscs(UStaticMeshComponent* Mesh, bool LockTranslationX, bool LockTranslationY, bool LockTranslationZ, bool LockRotationX, bool LockRotationY, bool LockRotationZ);

	/**
	* Causes a crash.
	*/
	UFUNCTION(BlueprintCallable, Category = "Helpers", Meta = (CompactNodeTitle = "- CRASH -", DisplayName = "Crash"))
	static void Crash();

};
