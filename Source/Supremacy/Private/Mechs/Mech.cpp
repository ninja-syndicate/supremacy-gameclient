#include "Mechs/Mech.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

#include "Weapons/Weapon.h"

DEFINE_LOG_CATEGORY(LogMech);

// Sets default values
AMech::AMech() {}

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

bool AMech::IsInitialized() const
{
	return bIsInitialized;
}

AWeapon* AMech::GetWeaponBySlot_Implementation(int SlotIndex)
{
	// Assumes the `Weapons` array is sorted by slot.
	return SlotIndex >= 0 && SlotIndex < Weapons.Num() ? Weapons[SlotIndex] : nullptr;
}

void AMech::GetWeapons_Implementation(TArray<AWeapon*>& OutWeapons)
{
	OutWeapons = Weapons;
}