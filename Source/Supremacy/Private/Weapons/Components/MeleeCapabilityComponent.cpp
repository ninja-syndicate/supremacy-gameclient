// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/MeleeCapabilityComponent.h"

#include "Components/BoxComponent.h"

#include "Weapons/Weapon.h"
#include "Weapons/Components/WeaponAmmunitionComponent.h"

// Sets default values for this component's properties
UMeleeCapabilityComponent::UMeleeCapabilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UMeleeCapabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Owner is invalid!"));
		return;
	}

	if (bUseBoxComp)
	{
		TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(UBoxComponent::StaticClass(), MeleeBoxCompTagName);
		if (Components.Num() > 1)
		{
			UE_LOG(LogWeapon, Warning, TEXT("UMeleeCapabilityComponent: Multiple melee box components aren't supported yet. Using the first one as a fallback."));
		}

		UWeaponAmmunitionComponent* AmmoComp = GetOwner()->FindComponentByClass<UWeaponAmmunitionComponent>();
		if (!AmmoComp)
		{
			// For now, if it has no ammo comp, always melee. TODO: Provide options.
			bSwitchToMeleePose = true;
		}
		else
		{
			// Bind event on zero ammo so it can switch to melee pose when out of ammo.
			AmmoComp->OnZeroAmmo.AddDynamic(this, &UMeleeCapabilityComponent::HandleNoAmmo);
		}
	}
}

void UMeleeCapabilityComponent::HandleNoAmmo()
{
	bSwitchToMeleePose = true;
}

// Called every frame
void UMeleeCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

