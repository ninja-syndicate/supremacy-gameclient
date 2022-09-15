#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWeaponType_Minigun = 0 UMETA(DisplayName = "Minigun"),
	EWeaponType_PlasmaGun UMETA(DisplayName = "Plasma Gun"),
	EWeaponType_Flak UMETA(DisplayName = "Flak"),
	EWeaponType_MachineGun UMETA(DisplayName="Machine Gun"),
	EWeaponType_MissileLauncher UMETA(DisplayName="Missile Launcher"),
	EWeaponType_LaserBeam UMETA(DisplayName="Laser Beam"),
	EWeaponType_Cannon UMETA(DisplayName="Cannon"),
	EWeaponType_GrenadeLauncher UMETA(DisplayName="Grenade Launcher"),
	EWeaponType_BFG UMETA(DisplayName="BFG"),
	EWeaponType_Flamethrower UMETA(DisplayName="Flamethrower"),
	EWeaponType_Sword UMETA(DisplayName="Sword"),
	EWeaponType_SniperRifle UMETA(DisplayName="SniperRifle"),
	EWeaponType_Rifle UMETA(DisplayName="Rifle"),
	EWeaponType_LightningGun UMETA(DisplayName="Lightning Gun"),
};

const TMap<FString, EWeaponType> StringToEWeaponType = {
	{ "Minigun", EWeaponType::EWeaponType_Minigun },
	{ "Plasma Gun", EWeaponType::EWeaponType_PlasmaGun },
	{ "Flak", EWeaponType::EWeaponType_Flak },
	{ "Machine Gun", EWeaponType::EWeaponType_MachineGun },
	{ "Missile Launcher", EWeaponType::EWeaponType_MissileLauncher },
	{ "Laser Beam", EWeaponType::EWeaponType_LaserBeam },
	{ "Cannon", EWeaponType::EWeaponType_Cannon },
	{ "Grenade Launcher", EWeaponType::EWeaponType_GrenadeLauncher },
	{ "BFG", EWeaponType::EWeaponType_BFG },
	{ "Flamethrower", EWeaponType::EWeaponType_Flamethrower },
	{ "Sword", EWeaponType::EWeaponType_Sword },
	{ "Sniper Rifle", EWeaponType::EWeaponType_SniperRifle },
	{ "Rifle", EWeaponType::EWeaponType_Rifle },
	{ "Lightning Gun", EWeaponType::EWeaponType_LightningGun }
};

