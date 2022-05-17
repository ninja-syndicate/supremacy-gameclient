// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MovementFragment.generated.h"

/**
 *
 */
USTRUCT()
struct FMovementFragment : public FMassFragment
{
	GENERATED_BODY()

	FVector Target;
};