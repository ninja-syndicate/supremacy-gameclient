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

	if (!GetOwner()->GetInstigator())
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Invalid instigator!"));
		return;
	}

	if (!bUseBoxComp)
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Not using box component is currently not supported."));
		return;
	}

	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(UBoxComponent::StaticClass(), MeleeBoxCompTagName);
	if (Components.Num() == 0)
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Needs a UBoxComponent to work."));
		return;
	}

	if (Components.Num() > 1)
	{
		UE_LOG(LogWeapon, Warning, TEXT("UMeleeCapabilityComponent: Multiple melee box components aren't supported yet. Using the first one as a fallback."));
	}
	MeleeBoxComp = Cast<UBoxComponent>(Components[0]);

	UWeaponAmmunitionComponent* AmmoComp = GetOwner()->FindComponentByClass<UWeaponAmmunitionComponent>();
	if (!AmmoComp)
	{
		// For now, if it has no ammo comp, always melee. TODO: Provide options.
		bSwitchToMeleePose = true;
	}
	else
	{
		bSwitchToMeleePose = !AmmoComp->HasAmmo();
		AmmoComp->OnAmmoChanged.AddDynamic(this, &UMeleeCapabilityComponent::HandleAmmoChanged);
	}
}

void UMeleeCapabilityComponent::HandleAmmoChanged(int CurrentAmmo)
{
	bSwitchToMeleePose = CurrentAmmo <= 0;
}

bool UMeleeCapabilityComponent::TriggerMelee_Implementation()
{
	// For now, the main logic will be implemented in the blueprints.
	return true;
}

// Called every frame
void UMeleeCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

