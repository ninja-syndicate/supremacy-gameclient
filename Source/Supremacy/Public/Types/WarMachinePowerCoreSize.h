#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWarMachinePowerCoreSize : uint8
{
	WarMachineCoreSize_Small = 0 UMETA(DisplayName = "Small"),
	WarMachineCoreSize_Medium UMETA(DisplayName = "Medium"),
	WarMachineCoreSize_Large UMETA(DisplayName = "Large")
};

const TMap<FString, EWarMachinePowerCoreSize> StringToEWarMachinePowerCoreSize = {
	{ "SMALL", EWarMachinePowerCoreSize::WarMachineCoreSize_Small },
	{ "MEDIUM", EWarMachinePowerCoreSize::WarMachineCoreSize_Medium },
	{ "LARGE", EWarMachinePowerCoreSize::WarMachineCoreSize_Large }
};

