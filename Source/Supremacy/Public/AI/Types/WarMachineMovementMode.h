#pragma once

#include "CoreMinimal.h"
#include "WarMachineMovementMode.generated.h"

UENUM(BlueprintType)
enum class EWarMachineMovementMode : uint8
{
	WARMACHINE_MOVE_Walk = 0 UMETA(DisplayName = "Walk"),
	WARMACHINE_MOVE_Sprint UMETA(DisplayName = "Sprint"),
};
