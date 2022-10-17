// Fill out your copyright notice in the Description page of Project Settings.


#include "Avoidance/AvoidanceSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
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

bool UAvoidanceSubsystem::CalcAgentBounds(APawn* Agent, float& OutCylinderRadius, float& OutCylinderHeight)
{
	const UPawnMovementComponent* MoveComp = Agent->GetMovementComponent();
	if (!MoveComp) return false;
	if (!MoveComp->UpdatedComponent) return false;

	float CylinderRadius = 0.0f;
	float CylinderHeight = 0.0f;
	MoveComp->UpdatedComponent->CalcBoundingCylinder(CylinderRadius, CylinderHeight);

	OutCylinderRadius = CylinderRadius;
	OutCylinderHeight = CylinderHeight;
	return true;
}

bool UAvoidanceSubsystem::Separation(APawn* Agent, FVector& OutSeparationForce)
{
	if (!IsValid(Agent)) return false;

	const FAgentAvoidanceSettings* AvoidanceSettings = Agents.Find(Agent);
	if (!AvoidanceSettings) return false;

	OutSeparationForce = GetSeparationForce(Agent, *AvoidanceSettings);
	return true;
}

FVector UAvoidanceSubsystem::GetSeparationForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings)
{
	// Ideally, need agent, obstacle, and environemnt separation range.

	// Fail-fast on invalid configurations.
	if (AvoidanceSettings.AgentRadius <= 0) return FVector::ZeroVector;
	if (AvoidanceSettings.SeparationQueryRange <= 0) return FVector::ZeroVector;
	if (AvoidanceSettings.MaxSeparationForce <= 0) return FVector::ZeroVector;

	FVector SeparationVector = FVector::ZeroVector;
	for (auto It = Agents.CreateIterator(); It; ++It)
	{
		const APawn* OtherAgent = It.Key();

		// Skip self.
		if (OtherAgent == Agent) continue;

		// Calculate a direction to this agent and magnitude.
		const FVector ToThisAgentDirection = Agent->GetActorLocation() - OtherAgent->GetActorLocation();
		const float Magnitude = ToThisAgentDirection.Length();

		// Skip if the other agent is too far away (i.e. outside the separation query range).
		if (Magnitude >= AvoidanceSettings.SeparationQueryRange) continue;

		const FAgentAvoidanceSettings OtherAgentAvoidanceSettings = It.Value();

		// Calculate total agent radius (this agent radius + other agent radius) that needs to be considered.
		const float TotalAgentRadius = AvoidanceSettings.AgentRadius + OtherAgentAvoidanceSettings.AgentRadius;

		// Calculate the separation force required.
		const float SeparationForce = FMath::Min(AvoidanceSettings.MaxSeparationForce * (TotalAgentRadius / Magnitude), AvoidanceSettings.MaxSeparationForce);
		const FVector NormalizedDirection = ToThisAgentDirection.GetSafeNormal();

		SeparationVector += NormalizedDirection * SeparationForce;
	}
	return SeparationVector.GetClampedToMaxSize(AvoidanceSettings.MaxSeparationForce);
}