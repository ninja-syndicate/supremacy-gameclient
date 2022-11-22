// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechHackComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "Components/SkeletalMeshComponent.h"

#include "Weapons/Weapon.h"
#include "Weapons/WeaponizedInterface.h"

// NOTE: This file is currently WIP. Not done yet.

// Sets default values for this component's properties
UMechHackComponent::UMechHackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMechHackComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UMechHackComponent: Owner is not a pawn!"));
		return;
	}

	// The hack effect will be attached to the mesh component if available.
	UActorComponent* Comp = OwnerPawn->GetComponentByClass(USkeletalMeshComponent::StaticClass());
	OwnerMeshComp = Cast<USkeletalMeshComponent>(Comp);

	InitHackDuration();
	bIsInitialized = true;
}

void UMechHackComponent::InitHackDuration_Implementation()
{
	// Base implementation cannot access the ability stats. So InitHackDuration will be implemented in blueprints.
}

void UMechHackComponent::Hack()
{
	if (!bIsInitialized) return;
	if (bIsHacked) return;  // If already hacked, simply ignore.

	if (OwnerPawn->Implements<UWeaponizedInterface>())
	{
		TArray<AWeapon*> Weapons;
		IWeaponizedInterface::Execute_GetWeapons(OwnerPawn, Weapons);
	
		for (AWeapon* Weapon : Weapons)
		{
			// Remember the weapon states to restore when unhacked.
			FWeaponState WeaponState;
			WeaponState.Slot = Weapon->Struct.Socket_Index;
			WeaponState.bIsTriggered = Weapon->IsTriggered();
			WeaponState.bCanFriendlyFire = Weapon->CanFriendlyFire();
			WeaponStates.Add(WeaponState);

			// Release the weapon and set it to do friendly fire.
			Weapon->Release();
			Weapon->SetFriendlyFire(true);
		}
	}
	AddHackEffect();

	// TODO: If player controlled, replace its controller with AI controller.
	GetWorld()->GetTimerManager().SetTimer(HackTimerHandle, this, &UMechHackComponent::Unhack, HackDuration, false, 0);
	// TODO: Change the script to AI begin call, and cancel queries.
	// TODO: Send an event to the server.

	bIsHacked = true;
}

void UMechHackComponent::Unhack()
{
	for (const FWeaponState& WeaponState : WeaponStates)
	{
		AWeapon* Weapon = IWeaponizedInterface::Execute_GetWeaponBySlot(OwnerPawn, WeaponState.Slot);
		if (!IsValid(Weapon)) continue;

		// TODO: Need a way to check if it was previously player controlled. Release the weapon in that case.
		if (OwnerPawn->IsPlayerControlled())
		{
			// Also, check if the player is holding the button... and release/trigger that way.
			Weapon->Release();
		}
		else if (WeaponState.bIsTriggered)
		{
			// If AI-controlled previously and the weapon was triggered, then trigger the weapon to maintain
			// the same state as the script.
			Weapon->Trigger();
		}
		Weapon->SetFriendlyFire(WeaponState.bCanFriendlyFire);
	}
	// Empty the weapon states.
	WeaponStates.Empty();

	bIsHacked = false;
}

void UMechHackComponent::AddHackEffect_Implementation()
{
	if (!OwnerMeshComp) return;
	if (!HackNiagaraSystem) return;

	HackNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		HackNiagaraSystem, 
		OwnerMeshComp, 
		FName("None"), 
		FVector::ZeroVector, 
		FRotator::ZeroRotator, 
		EAttachLocation::SnapToTarget,
		false);
}

void UMechHackComponent::SaveWeaponStates()
{

}

// Called every frame
void UMechHackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

