#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWarMachineModelType : uint8
{
	WarMachineModelType_Humanoid = 0 UMETA(DisplayName = "Humanoid"),
	WarMachineModelType_Platform UMETA(DisplayName = "Platform")
};

const TMap<FString, EWarMachineModelType> StringToEWarMachineModelType = {
	{ "HUMANOID", EWarMachineModelType::WarMachineModelType_Humanoid },
	{ "PLATFORM", EWarMachineModelType::WarMachineModelType_Platform }
};

