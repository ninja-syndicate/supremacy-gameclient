// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechHackComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
		WeaponStates.Reserve(Weapons.Num());
		for (AWeapon* Weapon : Weapons)
		{
			// Remember the weapon states to restore when unhacked.
			const bool bIsTriggered = Weapon->IsTriggered();
			WeaponStates[Weapon->Struct.Socket_Index] = bIsTriggered;

			// Release the weapon.
			Weapon->Release();
		}
		//OwnerPawn->
	}
	bIsHacked = true;
}

void UMechHackComponent::Unhack()
{

	// Empty the weapon states.
	WeaponStates.Empty();
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

