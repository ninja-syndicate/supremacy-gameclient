// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SupremacyGameState.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ASupremacyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void HandleMatchHasStarted() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchStartedDelegate);
	UPROPERTY(BlueprintAssignable, Replicated)
	FMatchStartedDelegate OnMatchStarted;
};
