#pragma once

#include "PayloadBattleStart.generated.h"

USTRUCT(BlueprintType)
struct FPayloadBattleStart_WarMachine {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Participant_ID;

	FPayloadBattleStart_WarMachine(): Participant_ID(0) {}
};

USTRUCT(BlueprintType)
struct FPayloadBattleStart {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Client_Build_No;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Map_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPayloadBattleStart_WarMachine> War_Machines;
};
