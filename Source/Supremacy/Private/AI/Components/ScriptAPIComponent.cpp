// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/ScriptAPIComponent.h"

// Sets default values for this component's properties
UScriptAPIComponent::UScriptAPIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UScriptAPIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UScriptAPIComponent::WeaponTrigger(int Slot, FVector Location)
{
	// stub
	return true;
}

bool UScriptAPIComponent::WeaponRelease(int Slot)
{
	return true;
}

void UScriptAPIComponent::EnableScript()
{
	bIsScriptEnabled = true;
}

void UScriptAPIComponent::DisableScript()
{
	bIsScriptEnabled = false;
}

// Called every frame
void UScriptAPIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

