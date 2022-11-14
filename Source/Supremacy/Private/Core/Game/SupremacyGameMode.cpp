// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/SupremacyGameMode.h"
#include "Core/Game/SupremacyGameState.h"

ASupremacyGameMode::ASupremacyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GameStateClass = ASupremacyGameState::StaticClass();

	// For now, always set ready to start match to true until blueprint stuff are moved to C++.
	bReadyToStartMatch = true;
}

bool ASupremacyGameMode::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();

	// bDelayedStart should be set accordingly.
	// bDelayedStart ?
	// 
	// For now, use the parent implementation. But should ideally use the variables.
	// return bReadyToStartMatch;
}

void ASupremacyGameMode::StartMatch()
{
	if (!bReadyToStartMatch)
	{
		UE_LOG(LogTemp, Error, TEXT("ASupremacyGameMode: StartMatch() should not be called manually. Set bReadyToStartMatch to true to start the match."));
		return;
	}

	Super::StartMatch();

	// Uncomment below after navitisation into c++ is done and when this StartMatch() is actually used for stating the match.
	/*
	ASupremacyGameState* SupremacyGameState = GetGameState<ASupremacyGameState>();
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("ASupremacyGameMode: Invalid game state!"));
		return;
	}
	SupremacyGameState->MulticastOnMatchStarted();
	*/
}