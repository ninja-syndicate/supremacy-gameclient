// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "RandomMovementProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API URandomMovementProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	URandomMovementProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
