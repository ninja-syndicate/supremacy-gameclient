// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "WarMachineFollowingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UWarMachineFollowingComponent : public UCrowdFollowingComponent
{
	GENERATED_BODY()
public:
	virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const override;

private:
	UPROPERTY(EditAnywhere)
	bool bEnableCustomCollisionRadius;

	UPROPERTY(EditAnywhere)
	float CollisionRadius;
};
