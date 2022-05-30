// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarMachineFollowingComponent.h"

void UWarMachineFollowingComponent::GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const
{
	Super::GetCrowdAgentCollisions(CylinderRadius, CylinderHalfHeight);

	// Overwrite the cylinder radius with custom one.
	if (bEnableCustomCollisionRadius)
	{
		CylinderRadius = CollisionRadius;
	}
}
