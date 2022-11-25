#include "Mechs/Mech.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

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
	DOREPLIFETIME_CONDITION(AMech, Weapons, COND_None);
}

void AMech::OnRep_SetWarMachineStruct()
{
	Setup();
}

void AMech::OnRep_Weapon()
{
	// NOTE: Currently, the initialization done condition is on all weapons set up. You can change this if you want.
	// Notify its initialization on replication.
	if (Weapons.Num() >= WarMachineStruct.Weapons.Num())
	{
		bIsInitialized = true;
		OnInitialized.Broadcast();
	}
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

	// Since the weapons variable is replicated, wait for the OnRep_Weapon to be called in the clients.
	if (HasAuthority())
	{
		Weapons.AddUnique(Weapon);

		// Manually call the OnRep_Weapon so standalone and listen server works.
		OnRep_Weapon();
	}
	OnWeaponEquipped.Broadcast(Weapon);
}
//~ End IWeaponizedInterface