// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypes.generated.h"

UCLASS()
class SUPREMACY_API UKineticDamageType : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class SUPREMACY_API UEnergyDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UEnergyDamageType();
};

UCLASS()
class SUPREMACY_API UExplosiveDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UExplosiveDamageType();
};

UCLASS()
class SUPREMACY_API UBattleZoneDamageType : public UDamageType
{
	GENERATED_BODY()
};