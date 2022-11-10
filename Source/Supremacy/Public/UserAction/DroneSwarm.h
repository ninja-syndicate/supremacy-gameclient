// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "DroneSwarm.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ADroneSwarm : public ABoid
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DistanceLimits)
	float DesiredDistance = 0.0f;

    virtual void Tick(float DeltaTime) override;

	void DroneFlock(TArray<ABoid*> Boids);

	FVector DroneSeek(FVector target);
};

