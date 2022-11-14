// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechMovementComponent.h"

void UMechMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Early return if the automatic braking deceleration distance calculation option is not enabled.
	if (!bEnableAutoBrakingDecelerationDistance) return;

	if (!bUseAccelerationForPaths)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMechMovementComponent: bUseAccelerationForPaths is not enabled! Braking deceleration will not work."));
		return;
	}
	if (!bUseFixedBrakingDistanceForPaths)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMechMovementComponent: bUseFixedBrakingDistanceForPaths is not enabled! Braking deceleration will not work."));
		return;
	}
	// Use the max walk speed to determine the path braking distance.
	FixedPathBrakingDistance = BrakingDecelerationMaxSpeedScale * MaxWalkSpeed;
}

void UMechMovementComponent::SetRVOAvoidanceEnabled(bool Enable)
{
	// If disabling, just disable as nothing needs to be done.
	if (!Enable)
	{
		SetAvoidanceEnabled(Enable);
		return;
	}

	// Otherwise, calculate the bounds of the agent and enable the RVO avoidance.
	float CylinderRadius = 0.0f, CylinderHeight = 0.0f;
	if (!CalcAgentBounds(CylinderRadius, CylinderHeight))
	{
		UE_LOG(LogTemp, Warning, TEXT("UMechMovementComponent: RVO avoidance cannot be enabled as agent bounds cannot be determined."));
		return;
	}
	AvoidanceConsiderationRadius = CylinderRadius * RadiusConsiderationMultiplier;
	SetAvoidanceEnabled(Enable);
}

bool UMechMovementComponent::CalcAgentBounds(float& OutCylinderRadius, float& OutCylinderHeight)
{;
	if (!UpdatedComponent) return false;

	float CylinderRadius = 0.0f;
	float CylinderHeight = 0.0f;
	UpdatedComponent->CalcBoundingCylinder(CylinderRadius, CylinderHeight);

	OutCylinderRadius = CylinderRadius;
	OutCylinderHeight = CylinderHeight;
	return true;
}