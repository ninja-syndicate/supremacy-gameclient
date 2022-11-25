// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/WeaponScaleComponent.h"

// Sets default values for this component's properties
UWeaponScaleComponent::UWeaponScaleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeaponScaleComponent::BeginPlay()
{
	Super::BeginPlay();

	/*
	if (!GetOwner())
	{
		UE_LOG(Log.., Error, TEXT(""));
		return;
	}

	if (!GetOwner()->GetInstigator())
	{

	}
	*/
}


// Called every frame
void UWeaponScaleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

