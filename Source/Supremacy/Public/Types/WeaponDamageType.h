#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponDamageType : uint8
{
	EWeaponDamageType_Kinetic = 0 UMETA(DisplayName = "Kinetic"),
	EWeaponDamageType_Energy UMETA(DisplayName = "Energy"),
	EWeaponDamageType_Explosive UMETA(DisplayName = "Explosive")
};

const TMap<FString, EWeaponDamageType> StringToEWeaponDamageType = {
	{ "Kinetic", EWeaponDamageType::EWeaponDamageType_Kinetic },
	{ "Energy", EWeaponDamageType::EWeaponDamageType_Energy },
	{ "Explosive", EWeaponDamageType::EWeaponDamageType_Explosive }
};

