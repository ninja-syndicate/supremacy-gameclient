#pragma once

#include "Types/AbilityID.h"
#include "PayloadBattleAbility.generated.h"

USTRUCT(BlueprintType)
struct FPayloadBattleAbility {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="game_client_ability_id"))
	EAbilityID GameClientAbilityID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="event_id"))
	FString EventID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="triggered_by_user_id"))
	FString TriggeredByUserID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="triggered_by_username"))
	FString TriggeredByUsername;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="game_location"))
	FVector2D GameLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="game_location_end"))
	FVector2D GameLocationEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="war_machine_hash"))
	FString WarMachineHash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="faction_id"))
	FString FactionID;

	FPayloadBattleAbility(): GameClientAbilityID(EAbilityID::AbilityID_Airstrike)
	{}
};
