// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Game/SupremacyGameState.h"
#include "Net/UnrealNetwork.h"

void ASupremacyGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	if (HasAuthority())
	{
		OnMatchStarted.Broadcast();
	}
}

void ASupremacyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASupremacyGameState, OnMatchStarted);
}
