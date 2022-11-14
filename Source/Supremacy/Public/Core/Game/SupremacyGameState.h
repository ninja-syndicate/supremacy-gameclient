// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Core/Game/SupremacyMatchState.h"
#include "SupremacyGameState.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ASupremacyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual bool HasMatchStarted() const override;
	virtual void HandleMatchHasStarted() override;

	UFUNCTION(Category = "Supremacy Game State", NetMulticast, Reliable, BlueprintCallable)
	void MulticastOnMatchStarted();
	virtual void MulticastOnMatchStarted_Implementation();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchStartedDelegate);
	UPROPERTY(Category = "Supremacy Game State", BlueprintAssignable, Replicated)
	FMatchStartedDelegate OnMatchStarted;

protected:
	UPROPERTY(Category = "Supremacy Game State", EditAnywhere, BlueprintReadWrite, Replicated)
	ESupremacyMatchState CurrentGameState = ESupremacyMatchState::MatchState_Default;
};
