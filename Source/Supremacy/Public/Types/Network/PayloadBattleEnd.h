#pragma once

#include "Types/DamageHistory.h"
#include "PayloadBattleEnd.generated.h"

USTRUCT(BlueprintType)
struct FPayloadBattleEnd_WarMachine {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDamageHistoryResultItem> Damage_History;

	FPayloadBattleEnd_WarMachine(): Health(0) {}
};


USTRUCT(BlueprintType)
struct FPayloadBattleEnd {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Win_Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPayloadBattleEnd_WarMachine> Winning_War_Machines;

	FPayloadBattleEnd(): Win_Condition("LAST_ALIVE") {}
};
