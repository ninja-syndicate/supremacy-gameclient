// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/CrowdFollowingComponent.h"
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
	// virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const override;

	// Override this to modify pathfinding query setting.
	virtual void OnPathfindingQuery(FPathFindingQuery& Query) override;

private:
	// UPROPERTY(EditAnywhere)
	// bool bEnableCustomCollisionRadius;

	// UPROPERTY(EditAnywhere)
	// float CollisionRadius;

	/**
	 * This option allows using the nearest navigable area as the start location when the agent is outside the navigable area.
	 * Can be used to recover when the agent somehow ends up outside the navigable area.
	 */
	UPROPERTY(Category = "War Machine Following Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseNearestNavAreaStart = false;

	UPROPERTY(Category = "War Machine Following Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNavigationSubsystem> NavSubsystem = nullptr;
};
