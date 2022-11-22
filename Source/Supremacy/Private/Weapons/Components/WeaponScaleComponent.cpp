// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/WeaponScaleComponent.h"

#include "Logger/SupremacyLogTypes.h"
#include "Weapons/WeaponizedInterface.h"

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

	if (!GetOwner())
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Invalid owner."));
		return;
	}

	APawn* Instigator = GetOwner()->GetInstigator();
	if (!Instigator)
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Invalid instigator."));
		return;
	}

	if (!Instigator->Implements<UWeaponizedInterface>())
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Instigator does not imlpement UWeaponizedInterface!"));
		return;
	}

	TArray<UStaticMeshComponent*> StaticComps;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticComps, true);

	const float WeaponBaseScale = IWeaponizedInterface::Execute_GetWeaponBaseScale(Instigator);
	for (UStaticMeshComponent* StaticComp : StaticComps)
	{
		//@todo - need to strict scale to just static mesh comp, not Niagara vfx.
		const FVector NewRelativeScale = StaticComp->GetRelativeScale3D() * WeaponBaseScale;
		StaticComp->SetRelativeScale3D(NewRelativeScale);
	}
}

// Called every frame
void UWeaponScaleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
