// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "RadiusInitializerProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API URadiusInitializerProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()
public:
	URadiusInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
