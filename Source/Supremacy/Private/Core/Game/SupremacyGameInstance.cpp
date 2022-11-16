// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/SupremacyGameInstance.h"

#include "Core/Damage/Type/EnergyDamageType.h"
#include "Core/Damage/Type/ExplosiveDamageType.h"

// @note - WIP DO NOT USE ANYTHING.
USupremacyGameInstance::USupremacyGameInstance() : Super()
{
	DamageTypes = { UEnergyDamageType::StaticClass(), UExplosiveDamageType::StaticClass() };
}