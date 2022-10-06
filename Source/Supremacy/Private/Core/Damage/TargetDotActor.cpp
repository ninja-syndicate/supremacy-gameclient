// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Damage/TargetDotActor.h"

bool ATargetDotActor::DestroyCondition_Implementation()
{
	const bool bSuperDestroyCondition = Super::DestroyCondition_Implementation();
	return !IsValid(TargetActor) || bSuperDestroyCondition;
}