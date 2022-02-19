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
	if (CrowdFollowingComponent)
	{
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Type::High);
		CrowdFollowingComponent->SetCrowdSeparation(bEnableSeparation);
		CrowdFollowingComponent->SetCrowdSeparationWeight(SeparationWeight);
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