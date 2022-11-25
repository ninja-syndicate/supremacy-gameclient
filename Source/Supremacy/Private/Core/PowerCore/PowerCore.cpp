// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PowerCore/PowerCore.h"

#include "Core/Gameplay/GameplayTags.h"

// Sets default values
APowerCore::APowerCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameplayTagContainer.AddTag(TAG_PowerCore);
}

void APowerCore::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APowerCore, GameplayTagContainer);
}

// Called when the game starts or when spawned
void APowerCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
