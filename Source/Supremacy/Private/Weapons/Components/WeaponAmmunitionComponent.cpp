// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/WeaponAmmunitionComponent.h"
#include "Weapons/Weapon.h"

// Sets default values for this component's properties
UWeaponAmmunitionComponent::UWeaponAmmunitionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponAmmunitionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponAmmunitionComponent, CurrentAmmo);
}

// Called when the game starts
void UWeaponAmmunitionComponent::BeginPlay()
{
	Super::BeginPlay();

	const AWeapon* Weapon = Cast<AWeapon>(GetOwner());
	if (!IsValid(Weapon))
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponAmmunitionComponent: Owner is not a weapon!"));
		return;
	}

	// Initialize current ammo and max ammo using the weapon struct.
	MaxAmmo = Weapon->Struct.Max_Ammo;
	CurrentAmmo = MaxAmmo;

	// Enable infinite ammo if max ammo is <= 0.
	if (MaxAmmo <= 0)
	{
		bEnableInfiniteAmmo = true;
	}
}

int UWeaponAmmunitionComponent::GetAmmo() const
{
	return CurrentAmmo;
}

bool UWeaponAmmunitionComponent::HasAmmo() const
{
	if (bEnableInfiniteAmmo) return true;
	
	return CurrentAmmo > 0;
}

bool UWeaponAmmunitionComponent::IsInfiniteAmmo() const
{
	return bEnableInfiniteAmmo;
}

void UWeaponAmmunitionComponent::ReduceAmmo()
{
	if (bEnableInfiniteAmmo) return;
	if (CurrentAmmo <= 0) return;

	--CurrentAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo);
}

void UWeaponAmmunitionComponent::RefillAmmo()
{
	CurrentAmmo = MaxAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo);
}

// Called every frame
void UWeaponAmmunitionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

