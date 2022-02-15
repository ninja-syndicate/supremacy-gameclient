// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

ACrowdAIController::ACrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (CrowdFollowingComponent) {
		// Note that the collision query range is set pretty high despite the agent radius being a lot smaller
		// (around 550), but the agents won't really avoid others unless set excessively.
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Type::High);
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(5000);
		CrowdFollowingComponent->SetCrowdSeparationWeight(2000);
	}
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!CrowdFollowingComponent) return;
}

void ACrowdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CrowdFollowingComponent) return;
}