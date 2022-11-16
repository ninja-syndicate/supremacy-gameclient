// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/SupremacyGameInstance.h"

#include "Core/Damage/DamageTypes.h"

USupremacyGameInstance::USupremacyGameInstance() : Super()
{
	DamageTypes = { 
		UKineticDamageType::StaticClass(),
		UEnergyDamageType::StaticClass(), 
		UExplosiveDamageType::StaticClass() 
	};
}

const TArray<TSubclassOf<UDamageType>>& USupremacyGameInstance::GetDamageTypes() const
{
	return DamageTypes;
}