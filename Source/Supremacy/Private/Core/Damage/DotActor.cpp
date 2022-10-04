// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Damage/DotActor.h"

// Sets default values
ADotActor::ADotActor()
{
	// Turn off tick by default.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADotActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADotActor::ApplyDamage_Implementation()
{
	// Base implementation does nothing.
}

// Called every frame
void ADotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}