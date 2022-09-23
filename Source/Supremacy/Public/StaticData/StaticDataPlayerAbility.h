// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataPlayerAbility.generated.h"

namespace StaticDataImporter
{
	class PlayerAbility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataPlayerAbility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::PlayerAbility;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 GameClientAbilityID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FColor Colour;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString ImageURL;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FColor TextColour;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString LocationSelectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString CreatedAt;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString RarityWeight;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 InventoryLimit;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 CooldownSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	bool DisplayOnMinimap;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 LaunchingDelaySeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString MinimapDisplayEffectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	FString MechDisplayEffectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 AnimationDurationSeconds;
};
