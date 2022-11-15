// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Game/SupremacyGameState.h"

#include "Net/UnrealNetwork.h"

void ASupremacyGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void ASupremacyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASupremacyGameState, OnMatchStarted);
	DOREPLIFETIME(ASupremacyGameState, OnMatchEnded);
	DOREPLIFETIME(ASupremacyGameState, CurrentGameState);
}

bool ASupremacyGameState::HasMatchStarted() const
{
	const bool bHasMatchStarted = Super::HasMatchStarted();

	// @note: Should Ending state, RoundEnd, GameEnd be considered as MatchStart?
	// If so probably better to create another function for IsDuringBattleMatch().
	return bHasMatchStarted && CurrentGameState == ESupremacyMatchState::MatchState_Battle;
}

void ASupremacyGameState::MulticastOnMatchStarted_Implementation()
{
	CurrentGameState = ESupremacyMatchState::MatchState_Battle;
	OnMatchStarted.Broadcast();
}

void ASupremacyGameState::MulticastOnMatchEnded_Implementation(const FFaction& Faction)
{
	CurrentGameState = ESupremacyMatchState::MatchState_RoundEnd;
	OnMatchEnded.Broadcast(Faction);
}