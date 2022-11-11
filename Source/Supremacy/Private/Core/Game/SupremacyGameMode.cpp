// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/SupremacyGameMode.h"
#include "Core/Game/SupremacyGameState.h"

ASupremacyGameMode::ASupremacyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GameStateClass = ASupremacyGameState::StaticClass();
}

void ASupremacyGameMode::StartMatch()
{
	Super::StartMatch();
}