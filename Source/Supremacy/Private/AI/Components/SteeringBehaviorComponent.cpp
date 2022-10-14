// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/SteeringBehaviorComponent.h"
#include "Avoidance/AvoidanceSubsystem.h"
#include "Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIController.h"

// Sets default values for this component's properties
USteeringBehaviorComponent::USteeringBehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USteeringBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	AvoidanceSubsystem = GetWorld()->GetSubsystem<UAvoidanceSubsystem>();
	if (!AvoidanceSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Failed to get a UAvoidanceSubsystem!"));
		return;
	}
	
	OwnerController = Cast<AAIController>(GetOwner());
	if (!OwnerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: The owner controller must be AAIController!"));
		return;
	}
	
	PossessedPawn = OwnerController->GetPawn();
	if (PossessedPawn)
	{
		Initialize(PossessedPawn);
	}
	OwnerController->OnPossessedPawnChanged.AddDynamic(this, &USteeringBehaviorComponent::OnPossessedPawnChanged);
}

void USteeringBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Fail-fast.
	if (!AvoidanceSubsystem) return;
	if (!OwnerController) return;
	if (!PossessedPawn) return;

	FVector SteeringForce = FVector::ZeroVector;
	SteeringForce += Separation();
}

void USteeringBehaviorComponent::OnPossessedPawnChanged()
{
	PossessedPawn = OwnerController->GetPawn();
	if (!IsValid(PossessedPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Invalid possessed pawn!"));
		return;
	}

	Initialize(PossessedPawn);
}

void USteeringBehaviorComponent::Initialize(APawn* Pawn)
{
	const UPawnMovementComponent* MoveComp = Pawn->GetMovementComponent();
	if (!MoveComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Invalid Pawn Movement Component! Failed to initialize."));
		return;
	}
	if (!MoveComp->UpdatedComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("USteeringBehaviorComponent: Invalid MoveComp->UpdatedComponent! Failed to initialize."));
		return;
	}

	float CylinderRadius = 0.0f;
	float CylinderHeight = 0.0f;
	MoveComp->UpdatedComponent->CalcBoundingCylinder(CylinderRadius, CylinderHeight);

	AgentRadius = CylinderRadius;
	SeparationQueryRange = AgentRadius * 12.0f;
}

FVector USteeringBehaviorComponent::Separation()
{
	// Ideally, store this radius and that radius to determine the required separation radius.

	// Ideally, need agent, obstacle, and environemnt separation range.

	const float MaxSeparationForce = 2500; // use max walk speed/acceleration? reconsider & decide later.

	if (AgentRadius <= 0) return FVector::ZeroVector;
	if (SeparationQueryRange <= 0) return FVector::ZeroVector;
	if (MaxSeparationForce <= 0) return FVector::ZeroVector;

	FVector SeparationVector = FVector::ZeroVector;

	for (const auto OtherAgent : AvoidanceSubsystem->GetAgents())
	{
		// Skip self.
		if (OtherAgent == PossessedPawn) continue;

		// Calculate to this agent direction and magnitude.
		const FVector ToThisAgentDirection = PossessedPawn->GetActorLocation() - OtherAgent->GetActorLocation();
		const float Magnitude = ToThisAgentDirection.Length();

		// Skip if the other agent is too far away (i.e. outside the separation query range).
		if (Magnitude >= SeparationQueryRange) continue;

		// TODO: Get the agent radius.
		const float OtherAgentRadius = 1000;
		const float TotalAgentRadius = AgentRadius + OtherAgentRadius;

		const float SeparationForce = FMath::Min(MaxSeparationForce * (TotalAgentRadius / Magnitude), MaxSeparationForce);
		const FVector NormalizedDirection = ToThisAgentDirection.GetSafeNormal();

		SeparationVector += NormalizedDirection * SeparationForce;
	}
	return SeparationVector.GetClampedToMaxSize(MaxSeparationForce);
}