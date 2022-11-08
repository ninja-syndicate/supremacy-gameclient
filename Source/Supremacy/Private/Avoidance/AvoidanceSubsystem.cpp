// Fill out your copyright notice in the Description page of Project Settings.


#include "Avoidance/AvoidanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Mechs/Components/MechMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void UAvoidanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAvoidanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAvoidanceSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (bAutoRegisterPlayerPawn)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!PlayerPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("UAvoidanceSubsystem: Player Pawn not found!"));
			return;
		}

		if (bUseRVOAvoidance)
		{
			UPawnMovementComponent* MoveComp = PlayerPawn->GetMovementComponent();
			UMechMovementComponent* MechMoveComp = Cast<UMechMovementComponent>(MoveComp);
			if (!MechMoveComp) return;

			MechMoveComp->SetRVOAvoidanceWeight(PlayerRVOAvoidanceWeight);
			MechMoveComp->SetAvoidanceGroup(EAvoidanceFlags::AvoidanceSubsystem_Player);
			MechMoveComp->SetGroupsToIgnore(EAvoidanceFlags::AvoidanceSubsystem_AI | EAvoidanceFlags::AvoidanceSubsystem_Player);
			MechMoveComp->SetRVOAvoidanceEnabled(true);
		}
		// TODO: Support other avoidance type.
	}
}

bool UAvoidanceSubsystem::RegisterAgent(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings)
{
	if (!IsValid(Agent)) return false;

	Agents.Add(Agent, AvoidanceSettings);
	return true;
}

bool UAvoidanceSubsystem::UnregisterAgent(APawn* Agent)
{
	const int32 NumRemoved = Agents.Remove(Agent);
	return NumRemoved > 0;
}

bool UAvoidanceSubsystem::Separation(APawn* Agent, FVector& OutSeparationForce)
{
	if (!IsValid(Agent)) return false;

	const FAgentAvoidanceSettings* AvoidanceSettings = Agents.Find(Agent);
	if (!AvoidanceSettings) return false;

	OutSeparationForce = GetSeparationForce(Agent, *AvoidanceSettings);
	return true;
}

bool UAvoidanceSubsystem::Steering(APawn* Agent, FVector& OutSteeringForce)
{
	if (!IsValid(Agent)) return false;

	const FAgentAvoidanceSettings* AvoidanceSettings = Agents.Find(Agent);
	if (!AvoidanceSettings) return false;

	OutSteeringForce = GetSteeringForce(Agent, *AvoidanceSettings);
	return true;
}

bool UAvoidanceSubsystem::ObstacleAvoidance(APawn* Agent, FVector& OutObstacleAvoidanceForce)
{
	// TODO: Implementation;
	OutObstacleAvoidanceForce = FVector::ZeroVector;
	return true;
}

FVector UAvoidanceSubsystem::GetSeparationForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings)
{
	// Fail-fast on invalid configurations.
	if (AvoidanceSettings.AgentRadius <= 0) return FVector::ZeroVector;
	if (AvoidanceSettings.SeparationQueryRange <= 0) return FVector::ZeroVector;
	if (AvoidanceSettings.MaxAccelerationSpeed <= 0) return FVector::ZeroVector;

	int Count = 0;
	FVector SeparationVector = FVector::ZeroVector;
	for (auto It = Agents.CreateIterator(); It; ++It)
	{
		const APawn* OtherAgent = It.Key();

		// Skip self.
		if (OtherAgent == Agent) continue;

		// Skip invalidy one.
		if (!IsValid(OtherAgent)) continue;

		// Calculate a direction to this agent and magnitude.
		const FVector ToThisAgentDirection = Agent->GetActorLocation() - OtherAgent->GetActorLocation();
		const float Distance = ToThisAgentDirection.Length();

		// Skip if the other agent is too far away (i.e. outside the separation query range).
		if (Distance >= AvoidanceSettings.SeparationQueryRange) continue;

		const FAgentAvoidanceSettings OtherAgentAvoidanceSettings = It.Value();

		// Calculate total agent radius (this agent radius + other agent radius) that needs to be considered.
		const float TotalAgentRadius = AvoidanceSettings.AgentRadius + OtherAgentAvoidanceSettings.AgentRadius;

		// Calculate the separation force required.
		const float MaxDist = FMath::Max(TotalAgentRadius, Distance);
		const float Strength = (TotalAgentRadius / MaxDist);
		const float SeparationForce = FMath::Min(AvoidanceSettings.MaxAccelerationSpeed * Strength, AvoidanceSettings.MaxAccelerationSpeed);

		const FVector NormalizedDirection = ToThisAgentDirection.GetSafeNormal();
		SeparationVector += NormalizedDirection * SeparationForce;
		++Count;
	}
	// No agents within the separation query range. No separation needed.
	if (Count == 0) return FVector::ZeroVector;

	SeparationVector /= Count;
	return SeparationVector.GetClampedToMaxSize(AvoidanceSettings.MaxAccelerationSpeed);
}

FVector UAvoidanceSubsystem::GetSteeringForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings)
{
	// Fail-fast on invalid configurations.
	if (AvoidanceSettings.MaxAccelerationSpeed <= 0) return FVector::ZeroVector;

	float ShortestCollisionTime = FLT_MAX;
	struct CollisionInfo {
		const APawn* Target = nullptr;
		float MinSeparation = 0.0f;
		float Distance = 0.0f;
		FVector ToThisAgentDirection = FVector::ZeroVector;
		FVector VelocityDiff = FVector::ZeroVector;
		float TotalRadius = 0.0f;
	} ShortestCollidingAgent;

	for (auto It = Agents.CreateIterator(); It; ++It)
	{
		const APawn* OtherAgent = It.Key();

		// Skip self.
		if (OtherAgent == Agent) continue;

		// Skip invalidy one.
		if (!IsValid(OtherAgent)) continue;

		const FVector ToThisAgentDirection = Agent->GetActorLocation() - OtherAgent->GetActorLocation();
		const FVector VelocityDiff = Agent->GetVelocity() - OtherAgent->GetVelocity();
		const float Distance = ToThisAgentDirection.Length();

		// Skip if too far away, i.e. outside the steering query range.
		if (Distance > AvoidanceSettings.SteeringQueryRange) continue;

		const float VelocityDiffSquared = VelocityDiff.SquaredLength();

		// Skip if the velocity diff squared is zero.
		if (VelocityDiffSquared == 0.0f) continue;

		const float CollisionTime = -ToThisAgentDirection.Dot(VelocityDiff) / (VelocityDiffSquared);
		const FVector Separation = ToThisAgentDirection + VelocityDiff * CollisionTime;
		const float MinSeparation = Separation.Length();
		const FAgentAvoidanceSettings OtherAgentAvoidanceSettings = It.Value();

		// Skip if the min separation required is greater than the total agent radius, i.e. no collision.
		const float TotalAgentRadius = AvoidanceSettings.AgentRadius + OtherAgentAvoidanceSettings.AgentRadius;
		if (MinSeparation > TotalAgentRadius) continue;

		// If the collision time is shorter, update the shortest colliding agent and time.
		if (CollisionTime > 0.0f && CollisionTime < ShortestCollisionTime)
		{
			ShortestCollisionTime = CollisionTime;
			ShortestCollidingAgent = { OtherAgent, MinSeparation, Distance, ToThisAgentDirection, VelocityDiff, TotalAgentRadius };
		}
	}

	// If no colliding agent, then no steering is needed.
	if (!ShortestCollidingAgent.Target) return FVector::ZeroVector;

	FVector SteeringForce = FVector::ZeroVector;
	if (ShortestCollidingAgent.MinSeparation <= 0 || ShortestCollidingAgent.Distance < ShortestCollidingAgent.TotalRadius)
	{
		SteeringForce = Agent->GetActorLocation() - ShortestCollidingAgent.Target->GetActorLocation();
	}
	else
	{
		SteeringForce = ShortestCollidingAgent.ToThisAgentDirection + ShortestCollidingAgent.VelocityDiff * ShortestCollisionTime;
	}
	const float MaxDist = FMath::Max(ShortestCollidingAgent.Distance, ShortestCollidingAgent.TotalRadius);
	const float Strength = MaxDist > 0 ? (ShortestCollidingAgent.TotalRadius / MaxDist) : 1; 

	SteeringForce.Normalize();
	return SteeringForce * AvoidanceSettings.MaxAccelerationSpeed * Strength;
}

FVector UAvoidanceSubsystem::GetObstacleAvoidanceForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings)
{
	// TODO: Implementation
	return FVector::ZeroVector;
}