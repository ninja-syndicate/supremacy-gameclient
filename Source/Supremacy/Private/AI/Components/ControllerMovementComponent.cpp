// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/ControllerMovementComponent.h"

#include "AIController.h"
#include "AITypes.h"
#include "Tasks/AITask.h"
#include "Tasks/AITask_MoveTo.h"

// Sets default values for this component's properties
UControllerMovementComponent::UControllerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UControllerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const auto Owner = GetOwner();
	if (!IsValid(Owner))
	{
		UE_LOG(LogTemp, Warning, TEXT("UControllerMovementComponent: Invalid owner."));
		return;
	}
	Controller = Cast<AAIController>(Owner);
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("UControllerMovementComponent: Owner is not an AIController!"));
		return;
	}
}


// Called every frame
void UControllerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EPathFollowingRequestResult::Type UControllerMovementComponent::MoveToLocation_Implementation(
	const FVector& Destination, 
	float AcceptanceRadius, 
	bool bReachTestIncludesAgentRadius, 
	bool bReachTestIncludesGoalRadius, 
	bool bStrafe, 
	bool bAllowPartialPath,
	UAITask_MoveTo* OutMoveToTask)
{
	FAIMoveRequest MoveRequest{Destination};
	MoveRequest.SetCanStrafe(bStrafe);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	MoveRequest.SetReachTestIncludesAgentRadius(bReachTestIncludesAgentRadius);
	MoveRequest.SetReachTestIncludesGoalRadius(bReachTestIncludesGoalRadius);
	MoveRequest.SetAllowPartialPath(bAllowPartialPath);
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetNavigationFilter(*FilterClass ? FilterClass : Controller->GetDefaultNavigationFilterClass());

	const FPathFollowingRequestResult RequestResult = Controller->MoveTo(MoveRequest);
	// return RequestResult.Code;

	UAITask_MoveTo* MoveToTask = Controller ? UAITask::NewAITask<UAITask_MoveTo>(*Controller, EAITaskPriority::High) : nullptr;
	if (MoveToTask)
	{
		MoveToTask->SetUp(Controller, MoveRequest);
		// TRUE for actor.
		MoveToTask->SetContinuousGoalTracking(false);
	}
	return RequestResult.Code;
	// return MoveToTask;
}

bool UControllerMovementComponent::MoveToActor_Implementation(
	AActor* TargetActor,
	float AcceptanceRadius,
	bool bReachTestIncludesAgentRadius,
	bool bReachTestIncludesGoalRadius,
	bool bStrafe,
	bool bAllowPartialPath,
	bool bTrackMovingGoal)
{
	// STUB
	return true;

	/*
	FAIMoveRequest MoveRequest;


	if (!bTrackMovingGoal) return MoveToLocation(TargetActor->GetActorLocation(), AcceptanceRadius, bReachTestIncludesAgentRadius, bReachTestIncludesAgentRadius, bStrafe, bAllowPartialPath, bTrackMovingGoal);
	*/

}