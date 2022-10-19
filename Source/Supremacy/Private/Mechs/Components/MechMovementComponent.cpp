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
	FixedPathBrakingDistance = BrakingDecelerationMaxSpeedScale * GetMaxSpeed();	
}

float UMechMovementComponent::GetMaxSpeed() const
{
	// Get the max speed and fallback to max walk speed if the movement mode is not set (thus have MaxSpeed of 0).
	const float MaxSpeed = Super::GetMaxSpeed();
	return MaxSpeed > 0 ? MaxSpeed : MaxWalkSpeed;
}