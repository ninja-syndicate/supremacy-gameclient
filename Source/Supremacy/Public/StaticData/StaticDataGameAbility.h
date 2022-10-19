// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticDataBaseRecord.h"
#include "UObject/Object.h"
#include "StaticDataFaction.h"
#include "StaticDataBattleAbility.h"
#include "StaticDataGameAbility.generated.h"

namespace StaticDataImporter
{
	class GameAbility;
}

UCLASS(BlueprintType)
class SUPREMACY_API UStaticDataGameAbility : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::GameAbility;
	
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 GameClientAbilityID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FColor Colour;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString ImageURL;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 SupsCost;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FColor TextColour;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 CurrentSups;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString DeletedAt;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 LaunchingDelaySeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool DisplayOnMinimap;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 AnimationDurationSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool ShouldCheckTeamKill;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	int32 MaximumTeamKillTolerantCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	bool IgnoreSelfKill;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	//TODO
	FString MechDisplayEffectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	//TODO
	FString MinimapDisplayEffectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	//TODO
	FString Level;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	//TODO
	FString LocationSelectType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fields", meta = (AllowPrivateAccess = true))
	int32 CountPerBattle;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataFaction* Faction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataBattleAbility *BattleAbility;
};
