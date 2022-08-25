#pragma once

#include "Types/WarMachineStruct.h"
#include "PayloadBattleInit.generated.h"

USTRUCT(BlueprintType)
struct FPayloadBattleInit {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Battle_Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Map_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWarMachineServerStruct> War_Machines;

	FPayloadBattleInit(): Battle_Number(0) {}
};
