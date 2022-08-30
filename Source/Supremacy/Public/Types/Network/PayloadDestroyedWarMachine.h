#pragma once

#include "Types/DamageHistory.h"
#include "PayloadDestroyedWarMachine.generated.h"

USTRUCT(BlueprintType)
struct FPayloadDestroyedWarMachine {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Destroyed_War_Machine_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Killed_By_War_Machine_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Related_Event_ID_String;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Killed_By;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Participant_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDamageHistoryResultItem> Damage_History;

	FPayloadDestroyedWarMachine() : Participant_ID(0) {}
};
