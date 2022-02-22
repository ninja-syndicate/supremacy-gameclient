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
	/** Whether to enable crowd separation or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableSeparation;

	/** The weight applied to the separation of the agents. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	float SeparationWeight;

	/** The range to check for the collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	float CollisionQueryRange;

	/** Slowdown the agent when it reaches close to the goal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableSlowdownAtGoal;

	/** Reference to the current crowd following component. */
	class UCrowdFollowingComponent* CrowdFollowingComponent;
};
