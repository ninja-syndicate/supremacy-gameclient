// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarMachineFollowingComponent.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"

#include "Navigation/NavigationSubsystem.h"
#include "Avoidance/AvoidanceSubsystem.h"

#include "DrawDebugHelpers.h"

void UWarMachineFollowingComponent::BeginPlay()
{
	Super::BeginPlay();

	NavSubsystem = GetWorld()->GetSubsystem<UNavigationSubsystem>();
	if (!NavSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to get a UNavigationSubsystem!"));
	}

	AvoidanceSubsystem = GetWorld()->GetSubsystem<UAvoidanceSubsystem>();
	if (!AvoidanceSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to get a UAvoidanceSubsystem!"));
		return;
	}

	OwnerController = Cast<AAIController>(GetOwner());
	if (!OwnerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: The owner controller must be AAIController!"));
		return;
	}

	PossessedPawn = OwnerController->GetPawn();
	if (PossessedPawn)
	{
		RegisterAgent(PossessedPawn);
	}
	OwnerController->OnPossessedPawnChanged.AddDynamic(this, &UWarMachineFollowingComponent::OnPossessedPawnChanged);
}

void UWarMachineFollowingComponent::FollowPathSegment(float DeltaTime)
{
	if (!Path.IsValid() || MovementComp == nullptr)
	{
		return;
	}

	const FVector CurrentLocation = MovementComp->GetActorFeetLocation();
	const FVector CurrentTarget = GetCurrentTargetLocation();

	// set to false by default, we will set set this back to true if appropriate
	bIsDecelerating = false;

	const bool bAccelerationBased = MovementComp->UseAccelerationForPathFollowing();
	if (bAccelerationBased)
	{
		CurrentMoveInput = (CurrentTarget - CurrentLocation).GetSafeNormal();

		// TODO: Provide an option to disable slowdown at destination.
		if (bStopMovementOnFinish && (MoveSegmentStartIndex >= DecelerationSegmentIndex))
		{
			const FVector PathEnd = Path->GetEndLocation();
			const float DistToEndSq = FVector::DistSquared(CurrentLocation, PathEnd);
			const bool bShouldDecelerate = DistToEndSq < FMath::Square(CachedBrakingDistance);
			if (bShouldDecelerate)
			{
				bIsDecelerating = true;

				const float SpeedPct = FMath::Clamp(FMath::Sqrt(DistToEndSq) / CachedBrakingDistance, 0.0f, 1.0f);
				CurrentMoveInput *= SpeedPct;
			}
		}

		// Add avoidance and steering behavior.
		CurrentMoveInput += Avoidance(DeltaTime);
		if (bIsDecelerating)
		{
			// Only normalize if the resultant vector exceeds unit length.
			if (CurrentMoveInput.Length() > 1.0f)
				CurrentMoveInput.Normalize();
		}
		else
		{
			CurrentMoveInput.Normalize();
		}
		PostProcessMove.ExecuteIfBound(this, CurrentMoveInput);
		MovementComp->RequestPathMove(CurrentMoveInput);
	}
	else
	{
		// NOTE: Our AI doesn't use this code path. It uses acceleration code above.
		FVector MoveVelocity = (CurrentTarget - CurrentLocation) / DeltaTime;

		const int32 LastSegmentStartIndex = Path->GetPathPoints().Num() - 2;
		const bool bNotFollowingLastSegment = (MoveSegmentStartIndex < LastSegmentStartIndex);

		PostProcessMove.ExecuteIfBound(this, MoveVelocity);
		MovementComp->RequestDirectMove(MoveVelocity, bNotFollowingLastSegment);
	}
}

FVector UWarMachineFollowingComponent::Avoidance(float DeltaTime)
{
	if (!PossessedPawn) return FVector::ZeroVector;
	if (AvoidanceSettings.MaxSeparationForce == 0.0f) return FVector::ZeroVector;

	FVector AvoidanceForce = FVector::ZeroVector;
	FVector SeparationForce = FVector::ZeroVector;

	if (AvoidanceSubsystem->Separation(PossessedPawn, SeparationForce)) AvoidanceForce += SeparationForce;

	// Clamp the resultant avoidance vector and take ratio to map it between [0, 1].
	const FVector ClampedAvoidanceVector = AvoidanceForce.GetClampedToMaxSize(AvoidanceSettings.MaxSeparationForce);
	const float Ratio = ClampedAvoidanceVector.Length() / AvoidanceSettings.MaxSeparationForce;

	// TEST: Visualization only
	const FVector StartLocation = PossessedPawn->GetActorLocation();
	const FVector EndLocation = StartLocation + ClampedAvoidanceVector;  // clamp here for visualization
	if (!ClampedAvoidanceVector.IsNearlyZero())
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 1, 0, 50);

	return ClampedAvoidanceVector * Ratio;
}

void UWarMachineFollowingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWarMachineFollowingComponent::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (!IsValid(NewPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Invalid possessed pawn!"));
		return;
	}
	RegisterAgent(NewPawn);
}

void UWarMachineFollowingComponent::RegisterAgent(APawn* Pawn)
{
	// If the custom avoidance setting is not enabled, try to determine appropriate avoidance settings from the pawn.
	if (!bEnableCustomAvoidanceSettings)
	{
		// Otherwise, 
		float CylinderRadius = 0.0f;
		float CylinderHeight = 0.0f;
		const bool bSuccess = AvoidanceSubsystem->CalcAgentBounds(Pawn, CylinderRadius, CylinderHeight);
		if (!bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Failed to calculate agent bounds!"));
			return;
		}
		AvoidanceSettings.AgentRadius = CylinderRadius;
		AvoidanceSettings.SeparationQueryRange = AvoidanceSettings.AgentRadius * 12.0f;
		AvoidanceSettings.MaxSeparationForce = 2500.0f; // use max walk speed/acceleration? reconsider & decide later.
	}

	// Register the agent with the specified avoidance settings.
	const bool bRegisterd = AvoidanceSubsystem->RegisterAgent(Pawn, AvoidanceSettings);
	if (!bRegistered)
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Failed to register the agent."));
		return;
	}
}

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

bool UWarMachineFollowingComponent::IsOnPath() const
{
	// Make it always on path to allow agent to get off-path for steering and avoidance purposes.
	return true;
}