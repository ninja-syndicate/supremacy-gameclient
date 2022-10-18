// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Damage/DotActor.h"
#include "TargetDotActor.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API ATargetDotActor : public ADotActor
{
	GENERATED_BODY()
	
public:
	virtual bool DestroyCondition_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	TObjectPtr<AActor> TargetActor = nullptr;

	/** If greater than 0 and the current TargetActor is not within this radius from this actor, this actor will be destroyed immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	float DespawnRadius = 0.0f;
};
