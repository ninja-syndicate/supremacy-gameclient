// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MechMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UMechMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	/** Enables RVO avoidance. The avoidance consideration range is automatically determined from the agent bounds. */
	UFUNCTION(Category = "Mech Movement Component", BlueprintCallable)
	void SetRVOAvoidanceEnabled(bool Enable);

	/** Retrieves the cylinder radius and the height of the agent. */
	UFUNCTION(Category = "Mech Movement Component", BlueprintCallable)
	bool CalcAgentBounds(float& OutCylinderRadius, float& OutCylinderHeight);

protected:
	/** 
	 * Whether to automatically calculate the braking deceleration distance based on the max speed and the deceleration max speed scale. 
	 * Must have `bUseAccelerationForPaths` and `bUseFixedBrakingDistanceForPaths` enabled for this to take effect, and this will override `FixedPathBrakingDistance` value.
	 */
	UPROPERTY(Category = "Mech Movement Component", EditAnywhere, BlueprintReadWrite)
	bool bEnableAutoBrakingDecelerationDistance = true;

	/** The scale multiplied to the max speed of the movement component to determine braking deceleration distance. */
	UPROPERTY(Category = "Mech Movement Component", EditAnywhere, BlueprintReadWrite, meta = (EditCondition="bEnableAutoBrakingDecelerationDistance"))
	float BrakingDecelerationMaxSpeedScale = 1.6f;

	/** The multiplier to the agnet radius to determine the avoidance consideration range. */
	UPROPERTY(Category = "Mech Movement Component", EditAnywhere, BlueprintReadWrite)
	float RadiusConsiderationMultiplier = 13.0f;
};
