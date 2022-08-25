#pragma once

#include "Types/WarMachineStruct.h"
#include "PayloadBattleInit.generated.h"

USTRUCT(BlueprintType)
struct FPayloadBattleInit {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="battle_id"))
	FString BattleID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="battle_number"))
	int BattleNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="map_name"))
	FString MapName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="war_machines"))
	TArray<FWarMachineServerStruct> WarMachines;

	FPayloadBattleInit(): BattleNumber(0) {}
};
