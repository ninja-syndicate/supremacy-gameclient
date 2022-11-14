// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SupremacyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ASupremacyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASupremacyGameMode(const FObjectInitializer& ObjectInitializer);

public:
	virtual void StartMatch() override;

protected:
	virtual bool ReadyToStartMatch_Implementation() override;

protected:
	/** Set this variable to true to start the match. */
	UPROPERTY(Category = "Supremacy Game Mode", EditAnywhere, BlueprintReadWrite)
	bool bReadyToStartMatch = false;
};
