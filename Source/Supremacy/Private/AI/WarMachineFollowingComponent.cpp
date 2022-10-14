// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarMachineFollowingComponent.h"

#include "NavigationSystem.h"
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

/*
void UWarMachineFollowingComponent::GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const
{
	Super::GetCrowdAgentCollisions(CylinderRadius, CylinderHalfHeight);

	// Overwrite the cylinder radius with custom one.
	if (bEnableCustomCollisionRadius)
	{
		CylinderRadius = CollisionRadius;
	}
}
*/

void UWarMachineFollowingComponent::OnPathfindingQuery(FPathFindingQuery& Query)
{
	Super::OnPathfindingQuery(Query);

	if (!bUseNearestNavAreaStart) return;
	if (!NavSubsystem) return;
	if (!MyNavData) return;

	// Use the specified start location to see if it's navigable.
	FVector NavLocation;
	const FVector QueryExtent = MyNavData->GetDefaultQueryExtent();
	const bool bIsNavigable = NavSubsystem->ProjectPointToNavigation(Query.StartLocation, QueryExtent, NavLocation);
	if (bIsNavigable)
	{
		Query.StartLocation = NavLocation;
		return;
	}

	// Otherwise, find the nearest navigable location and use that as a start location.
	FVector NearestNavLocation;
	const bool bSucceed = NavSubsystem->GetNearestNavigableAreaByExtent(Query.StartLocation, NearestNavLocation, QueryExtent, false);
	if (bSucceed)
	{
		Query.StartLocation = NearestNavLocation;
		return;
	}
}