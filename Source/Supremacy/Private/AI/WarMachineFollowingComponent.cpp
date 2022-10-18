// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarMachineFollowingComponent.h"

#include "Navigation/NavigationSubsystem.h"

void UWarMachineFollowingComponent::BeginPlay()
{
	Super::BeginPlay();

	NavSubsystem = GetWorld()->GetSubsystem<UNavigationSubsystem>();
	if (!NavSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to get a UNavigationSubsystem!"));
	}
}

void UWarMachineFollowingComponent::GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const
{
	Super::GetCrowdAgentCollisions(CylinderRadius, CylinderHalfHeight);

	// Overwrite the cylinder radius with custom one.
	if (bEnableCustomCollisionRadius)
	{
		CylinderRadius = CollisionRadius;
	}
}

void UWarMachineFollowingComponent::OnPathfindingQuery(FPathFindingQuery& Query)
{
	Super::OnPathfindingQuery(Query);

	if (!bUseNearestNavAreaStart) return;
	if (!NavSubsystem) return;
	if (NavSubsystem->IsNavigable(Query.StartLocation)) return;

	// Find the nearest navigable location and use that as a start location.
	FVector NearestNavLocation;
	const bool bSucceed = NavSubsystem->GetNearestNavigableArea(Query.StartLocation, NearestNavLocation);
	if (bSucceed)
	{
		Query.StartLocation = NearestNavLocation;
	}
}