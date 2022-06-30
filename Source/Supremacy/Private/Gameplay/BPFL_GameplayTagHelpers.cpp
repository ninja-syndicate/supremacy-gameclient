// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/BPFL_GameplayTagHelpers.h"

FGameplayTagContainer UBPFL_GameplayTagHelpers::GetAllTags(const FGameplayTagContainer& GameplayTagContainer)
{
	return GameplayTagContainer.GetGameplayTagParents();
}