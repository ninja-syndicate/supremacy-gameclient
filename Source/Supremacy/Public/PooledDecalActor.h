// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "Engine/Classes/Components/DecalComponent.h"
#include "PooledDecalActor.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API APooledDecalActor : public ADecalActor
{
	GENERATED_BODY()

public:
	void SetMaterial(UMaterialInstanceDynamic* Material, float SpawnTime, float LifeTime);
};
