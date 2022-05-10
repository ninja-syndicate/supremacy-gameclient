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

	if (AvoidanceType == EAvoidanceType::Unused1 || AvoidanceType == EAvoidanceType::Unused2)
	{
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: Unused avoidance type is being used."));
	}

	CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (!CrowdFollowingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: CrowdFollowingComponent is invalid. AI will not work properly..."));
	}
	else
	{
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(static_cast<ECrowdAvoidanceQuality::Type>(AvoidanceType.GetValue()));
		// CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Type::High);
		CrowdFollowingComponent->SetCrowdSeparation(bEnableSeparation);
		CrowdFollowingComponent->SetCrowdSeparationWeight(SeparationWeight);
		CrowdFollowingComponent->SetCrowdSlowdownAtGoal(bEnableSlowdownAtGoal);
		CrowdFollowingComponent->SetCrowdPathOptimizationRange(PathOptimizationRange);
		UE_LOG(LogTemp, Warning, TEXT("path optimization range: %f"), CrowdFollowingComponent->GetCrowdPathOptimizationRange());
	}
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACrowdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}