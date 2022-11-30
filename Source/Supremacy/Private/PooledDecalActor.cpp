// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledDecalActor.h"

void APooledDecalActor::SetMaterial(UMaterialInstanceDynamic* Material, float SpawnTime, float LifeTime) {
	UDecalComponent* DecalComponent = GetDecal();
	Material->SetScalarParameterValue("SpawnTime", SpawnTime);
	Material->SetScalarParameterValue("LifeTime", LifeTime);
	DecalComponent->SetMaterial(0, Material);
}