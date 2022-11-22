// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield/Shield.h"

#include "Net/UnrealNetwork.h"

#include "Core/Gameplay/GameplayTags.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add shield and damageable tag.
	GameplayTagContainer.AddTag(TAG_Shield);
	GameplayTagContainer.AddTag(TAG_Damageable);
}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShield, GameplayTagContainer);
}