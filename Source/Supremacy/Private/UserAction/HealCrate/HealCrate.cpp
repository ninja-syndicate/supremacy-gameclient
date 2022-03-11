// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAction/HealCrate/HealCrate.h"

// Sets default values
AHealCrate::AHealCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}