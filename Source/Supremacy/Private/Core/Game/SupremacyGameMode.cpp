// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/SupremacyGameMode.h"
#include "Core/Game/SupremacyGameState.h"

ASupremacyGameMode::ASupremacyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GameStateClass = ASupremacyGameState::StaticClass();

	// For now, always set ready to start match to true until blueprint stuff are moved to C++.
	bReadyToStartMatch = true;
}

void ASupremacyGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	SupremacyGameState = Cast<ASupremacyGameState>(GameState);
	if (!SupremacyGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("ASupremacyGameState: Game state is not ASupremacyGameState!"));
		return;
	}
}

bool ASupremacyGameMode::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();

	// bDelayedStart should be set accordingly based on the game mode.
	// bDelayedStart ?
	// 
	// For now, use the parent implementation. But should ideally use the variables.
	// return bReadyToStartMatch;
}

bool ASupremacyGameMode::ReadyToEndMatch_Implementation()
{
	return Super::ReadyToEndMatch_Implementation();
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
	SupremacyGameState->MulticastOnMatchStarted();
	*/
}

void ASupremacyGameMode::EndMatch()
{
	// Currently, this function is getting called in the Deathmatch game mode to end the match.
	Super::EndMatch();

	// Uncomment below after navitisation into c++ is done and when this EndMatch() is actually used for stating the match.
	// SupremacyGameState->MulticastOnMatchEnd();
}