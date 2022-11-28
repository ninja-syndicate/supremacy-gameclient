#include "Mechs/Mech.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Weapons/Weapon.h"
#include "Core/Gameplay/GameplayTags.h"

// Sets default values
AMech::AMech() 
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AMech::BeginPlay()
{
	Super::BeginPlay();
}

void AMech::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 

	DOREPLIFETIME_CONDITION(AMech, WarMachineStruct, COND_InitialOnly);
	DOREPLIFETIME(AMech, Weapons);
}

void AMech::OnRep_SetWarMachineStruct()
{
	Setup();
}

bool AMech::IsInitialized() const
{
	return bIsInitialized;
}

//~ Begin IWeaponizedInterface
AWeapon* AMech::GetWeaponBySlot_Implementation(int SlotIndex)
{
	// Assumes the `Weapons` array is sorted by slot.
	return SlotIndex >= 0 && SlotIndex < Weapons.Num() ? Weapons[SlotIndex] : nullptr;
}

void AMech::GetWeapons_Implementation(TArray<AWeapon*>& OutWeapons)
{
	OutWeapons = Weapons;
}

float AMech::GetWeaponBaseScale_Implementation() const
{
	return WeaponBaseScale;
}

void AMech::PostWeaponInit_Implementation(AWeapon* Weapon)
{
	// NOTE: This method assumes it is called after Weapon's BeginPlay().
	OnWeaponEquipped.Broadcast(Weapon);
	HandleWeaponEquipped(Weapon);
}
//~ End IWeaponizedInterface

void AMech::HandleWeaponEquipped(AWeapon* Weapon)
{
	// @todo - check whether weapon loading is complete.
	// Currently, nothing uses On Initialized event.
}