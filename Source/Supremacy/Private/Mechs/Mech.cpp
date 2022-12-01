#include "Mechs/Mech.h"

#include "Core/Game/SupremacyFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

#include "Weapons/Weapon.h"
#include "Core/Gameplay/GameplayTags.h"
#include "GameFramework/GameModeBase.h"
#include "StaticData/StaticData.h"
#include "UserAction/UserActionManager.h"

// Sets default values
AMech::AMech() 
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AMech::BeginPlay()
{
	Super::BeginPlay();

	// Get User Action Manager (for mech abilities)
	if (const auto GameMode = UGameplayStatics::GetGameMode(GetWorld()); GameMode)
	{
		UActorComponent *Component = GameMode->GetComponentByClass(UUserActionManager::StaticClass());
		if (Component)
			UserActionManager =  Cast<UUserActionManager>(Component);
	}
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

void AMech::UseMechAbility_Implementation(const EAbilityID Ability)
{
	// Get Cooldown
	UStaticData* StaticData = USupremacyFunctionLibrary::GetStaticData(GetWorld());
	if (!StaticData)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMech: StaticData is null."));
		return;
	}
	const float Cooldown = StaticData->GetAbilityCooldown(Ability);

	// On Cooldown?
	const float CurrentTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if (const float* UseTime = AbilityUseTimes.Find(Ability); UseTime != nullptr)
	{
		if (Cooldown == -1 || CurrentTime < *UseTime + Cooldown)
		{
			UE_LOG(LogTemp, Display, TEXT("AMech: Tried to use ability that's on cooldown"));
			return;
		}
	}

	// Check UserActionManager
	if (!UserActionManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMech: UserActionManager is null."));
		return;
	}

	// Spawn Ability
	UserActionManager->SpawnAbility(
		Ability,
		FVector2D(GetActorLocation()), FVector2D(),
		"",
		WarMachineStruct.OwnerID, WarMachineStruct.OwnerName,
		WarMachineStruct.Hash, WarMachineStruct.Faction.ID
		);

	// Set Cooldown
	AbilityUseTimes.Add(Ability, CurrentTime);

	OnMechAbilityUsed.Broadcast(Ability);
}
