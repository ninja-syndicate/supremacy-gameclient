// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Avoidance/AvoidanceSubsystem.h"
#include "WarMachineFollowingComponent.generated.h"

/**
 *
 */
UCLASS()
class SUPREMACY_API UWarMachineFollowingComponent : public UPathFollowingComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	// Override this to modify the agent path following direction and its velocity. 
	virtual void FollowPathSegment(float DeltaTime) override;

	// Override this to modify pathfinding query setting.
	virtual void OnPathfindingQuery(FPathFindingQuery& Query) override;

	// Override this to allow AI to get off-path for steering and avoidance purposes.
	virtual bool IsOnPath() const override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector Avoidance(float DeltaTime);
	void RegisterAgent(APawn* Pawn);

	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

private:
	/** The possessed pawn of the owning AI controller. */
	UPROPERTY(Category = "War Machine Following Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APawn> PossessedPawn = nullptr;

	/** Reference to the owner AI controller. */
	UPROPERTY(Category = "War Machine Following Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class AAIController> OwnerController = nullptr;

private:
	/** Reference to the navigation subsystem. */
	UPROPERTY(Category = "War Machine Following Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UNavigationSubsystem> NavSubsystem = nullptr;

	/**
	 * This option allows using the nearest navigable area as the start location when the agent is outside the navigable area.
	 * Can be used to recover when the agent somehow ends up outside the navigable area.
	 */
	UPROPERTY(Category = "War Machine Following Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseNearestNavAreaStart = false;

private:
	/** Reference to the avoidance subsystem. */
	UPROPERTY(Category = "AI Avoidance and Steering Behavior", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAvoidanceSubsystem> AvoidanceSubsystem = nullptr;

	UPROPERTY(Category = "AI Avoidance and Steering Behavior", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, EditCondition="bEnableCustomAvoidanceSettings"))
	FAgentAvoidanceSettings AvoidanceSettings;

	/** Toggle switch for the AI avoidance system. */
	UPROPERTY(Category = "AI Avoidance and Steering Behavior", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bEnableAvoidance = true;

	/** 
	 * By default, the avoidance settings are automatically determined from the pawn radius and its movement component settings.
	 * You can toggle this on to provide custom avoidance settings for debugging. 
	 */
	UPROPERTY(Category = "AI Avoidance and Steering Behavior", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bEnableCustomAvoidanceSettings = false;
};
