// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarMachineFollowingComponent.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Navigation/NavigationSubsystem.h"
#include "Avoidance/AvoidanceSubsystem.h"
#include "Mechs/Components/MechMovementComponent.h"

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
		RegisterAgent();
	}
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
		const bool bIsLastSegment = MoveSegmentStartIndex >= DecelerationSegmentIndex;
		const bool bConsiderDeceleration = bStopMovementOnFinish && bIsLastSegment;
		if (bConsiderDeceleration)
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

		if (bEnableAvoidance && !bEnableRVOAvoidance)
		{
			// Add separation and steering behaviors.
			if (!bIsLastSegment || bEnableSeparationOnDestination)
				CurrentMoveInput += Separation() * SeparationWeight;

			CurrentMoveInput += Steering() * SteeringWeight;
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

void UWarMachineFollowingComponent::OnNewPawn(APawn* NewPawn)
{
	if (HasBegunPlay())
	{
		// Unregister the previous possessed pawn if any.
		if (PossessedPawn)
		{
			UnregisterAgent();
		}
		// Return if it's unpossession.
		if (!NewPawn) return;
		
		// Otherwise register the new pawn.
		PossessedPawn = NewPawn;
		if (PossessedPawn)
		{
			RegisterAgent();
		}
	}
}

bool UWarMachineFollowingComponent::GetMaxAccelerationSpeed(float& OutMaxAccelerationSpeed)
{
	if (!PossessedPawn) return false;

	const UPawnMovementComponent* MoveComp = PossessedPawn->GetMovementComponent();
	if (!MoveComp) return false;

	const UCharacterMovementComponent* CharacterMoveComp = Cast<UCharacterMovementComponent>(MoveComp);
	if (!CharacterMoveComp)
	{
		// Use the pawn move comp max speed as the fallback.
		OutMaxAccelerationSpeed = MoveComp->GetMaxSpeed();
		return true;
	}
	OutMaxAccelerationSpeed = CharacterMoveComp->GetMaxAcceleration();
	return true;
}

void UWarMachineFollowingComponent::RegisterAgent()
{
	// If the custom avoidance setting is not enabled, try to determine appropriate avoidance settings from the pawn.
	if (!bEnableCustomAvoidanceSettings)
	{
		float CylinderRadius = 0.0f;
		float CylinderHeight = 0.0f;

		UPawnMovementComponent* MoveComp = PossessedPawn->GetMovementComponent();
		UMechMovementComponent* MechMoveComp = Cast<UMechMovementComponent>(MoveComp);
		if (!MechMoveComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to retrieve UMechMovementComponent!"));
			return;
		}

		bool bSuccess = MechMoveComp->CalcAgentBounds(CylinderRadius, CylinderHeight);
		if (!bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to calculate agent bounds!"));
			return;
		}

		float MaxAccelerationSpeed = 0.0f;
		bSuccess = GetMaxAccelerationSpeed(MaxAccelerationSpeed);
		if (!bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to calculate max acceleration speed!"));
			return;
		}
		AvoidanceSettings.AgentRadius = CylinderRadius * AgentRadiusMultiplier;
		AvoidanceSettings.SeparationQueryRange = AvoidanceSettings.AgentRadius * 13.0f;
		AvoidanceSettings.SteeringQueryRange = AvoidanceSettings.AgentRadius * 30.0f;
		AvoidanceSettings.MaxAccelerationSpeed = MaxAccelerationSpeed;
	}

	if (bEnableRVOAvoidance)
	{
		UPawnMovementComponent* MoveComp = PossessedPawn->GetMovementComponent();
		UMechMovementComponent* CharacterMoveComp = Cast<UMechMovementComponent>(MoveComp);
		if (!CharacterMoveComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: RVO can only be enabled on ACharacter!"));
			return;
		}
		CharacterMoveComp->SetRVOAvoidanceEnabled(true);
	}
	else
	{
		// Register the agent with the specified avoidance settings.
		const bool bRegisterd = AvoidanceSubsystem->RegisterAgent(PossessedPawn, AvoidanceSettings);
		if (!bRegistered)
		{
			UE_LOG(LogTemp, Warning, TEXT("UWarMachineFollowingComponent: Failed to register the agent."));
			return;
		}
	}
}

void UWarMachineFollowingComponent::UnregisterAgent()
{
	if (!AvoidanceSubsystem) return;

	AvoidanceSubsystem->UnregisterAgent(PossessedPawn);
}

FVector UWarMachineFollowingComponent::Separation()
{
	if (!PossessedPawn) return FVector::ZeroVector;
	if (AvoidanceSettings.MaxAccelerationSpeed == 0.0f) return FVector::ZeroVector;

	FVector SeparationForce = FVector::ZeroVector;

	const bool bSucceed = AvoidanceSubsystem->Separation(PossessedPawn, SeparationForce);
	if (!bSucceed) return FVector::ZeroVector;

	// Get the separation direction and map it to [0, 1] depending on the strength.
	const FVector SeparationDirectionNormal = SeparationForce.GetSafeNormal();
	const float Strength = SeparationForce.Length() / AvoidanceSettings.MaxAccelerationSpeed;

	return SeparationDirectionNormal * Strength;
}

FVector UWarMachineFollowingComponent::Steering()
{
	if (!PossessedPawn) return FVector::ZeroVector;
	if (AvoidanceSettings.MaxAccelerationSpeed == 0.0f) return FVector::ZeroVector;

	FVector SteeringForce = FVector::ZeroVector;

	const bool bSucceed = AvoidanceSubsystem->Steering(PossessedPawn, SteeringForce);
	if (!bSucceed) return FVector::ZeroVector;

	// Get the steering direction and map it to [0, 1] depending on the strength.
	const FVector SteeringDirectionNormal = SteeringForce.GetSafeNormal();
	const float Strength = SteeringForce.Length() / AvoidanceSettings.MaxAccelerationSpeed;

	return SteeringDirectionNormal * Strength;
}