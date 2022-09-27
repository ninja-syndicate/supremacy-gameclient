#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWarMachineBoostStat : uint8
{
	WarMachineBoostStat_Speed = 0 UMETA(DisplayName = "Speed"),
	WarMachineBoostStat_ShieldRegen UMETA(DisplayName = "ShieldRegen"),
	WarMachineBoostStat_Health UMETA(DisplayName = "Health")
};

const TMap<FString, EWarMachineBoostStat> StringToEWarMachineBoostStat = {
	{ "MECH_SPEED", EWarMachineBoostStat::WarMachineBoostStat_Speed },
	{ "MECH_HEALTH", EWarMachineBoostStat::WarMachineBoostStat_ShieldRegen },
	{ "SHIELD_REGEN", EWarMachineBoostStat::WarMachineBoostStat_Health }
};

