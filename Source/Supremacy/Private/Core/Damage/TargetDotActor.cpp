// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Damage/TargetDotActor.h"

bool ATargetDotActor::DestroyCondition_Implementation()
{
	if (!IsValid(TargetActor)) return true;

	const float DistToTarget = FVector::Distance(GetActorLocation(), TargetActor->GetActorLocation());
	if (DespawnRadius > 0 && DistToTarget >= DespawnRadius) return true;
	
	const bool bSuperDestroyCondition = Super::DestroyCondition_Implementation();
	return bSuperDestroyCondition;
}