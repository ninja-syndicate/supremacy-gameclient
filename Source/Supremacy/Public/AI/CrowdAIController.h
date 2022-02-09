// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ACrowdAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACrowdAIController(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
protected:
	/** Reference to the current crowd following component. */
	class UCrowdFollowingComponent* CrowdFollowingComponent;
};
