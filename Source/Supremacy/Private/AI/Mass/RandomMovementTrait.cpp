// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Mass/RandomMovementTrait.h"
#include "AI/Mass/MovementFragment.h"

void URandomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddFragment<FMovementFragment>();
}