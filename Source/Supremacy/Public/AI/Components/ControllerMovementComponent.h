// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tasks/AITask_MoveTo.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "ControllerMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UControllerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControllerMovementComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (AcceptanceRadius = 600, bReachTestIncludesAgentRadius = true, bReachTestIncludesGoalRadius = true, bAllowPartialPath = true))
	EPathFollowingRequestResult::Type MoveToLocation(
		const FVector& Destination, 
		float AcceptanceRadius, 
		bool bReachTestIncludesAgentRadius, 
		bool bReachTestIncludesGoalRadius, 
		bool bStrafe, 
		bool bAllowPartialPath,
		UAITask_MoveTo* OutMoveToTask);
	virtual EPathFollowingRequestResult::Type MoveToLocation_Implementation(
		const FVector& Destination,
		float AcceptanceRadius,
		bool bReachTestIncludesAgentRadius,
		bool bReachTestIncludesGoalRadius,
		bool bStrafe,
		bool bAllowPartialPath,
		UAITask_MoveTo* OutMoveToTask);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool MoveToActor(
		AActor* TargetActor,
		float AcceptanceRadius,
		bool bReachTestIncludesAgentRadius,
		bool bReachTestIncludesGoalRadius,
		bool bStrafe,
		bool bAllowPartialPath,
		bool bTrackMovingGoal);
	virtual bool MoveToActor_Implementation(
		AActor* TargetActor,
		float AcceptanceRadius,
		bool bReachTestIncludesAgentRadius,
		bool bReachTestIncludesGoalRadius,
		bool bStrafe,
		bool bAllowPartialPath,
		bool bTrackMovingGoal);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<class AAIController> Controller;
	TSubclassOf<UNavigationQueryFilter> FilterClass;
};
