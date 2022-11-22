// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/GameplayTagFunctionLibrary.h"

FGameplayTagContainer UGameplayTagFunctionLibrary::GetAllTags(const FGameplayTagContainer& GameplayTagContainer)
{
	return GameplayTagContainer.GetGameplayTagParents();
}