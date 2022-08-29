#pragma once

#include "Types/WarMachineStatus.h"
#include "PayloadWarMachineStatus.generated.h"

USTRUCT(BlueprintType)
struct FPayloadWarMachineStatus {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Event_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString War_Machine_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineStatus War_Machine_Status;

	FPayloadWarMachineStatus() {}
};