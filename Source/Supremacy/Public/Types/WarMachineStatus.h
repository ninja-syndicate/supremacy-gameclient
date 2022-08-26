#pragma once

#include "WarMachineStatus.generated.h"

USTRUCT(BlueprintType)
struct FWarMachineStatus {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Is_Hacked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Is_Stunned;

	FWarMachineStatus() : Is_Hacked(false), Is_Stunned(false) {}
};