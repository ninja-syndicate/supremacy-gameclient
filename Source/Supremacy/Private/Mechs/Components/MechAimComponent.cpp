// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechAimComponent.h"

#include "Mechs/Mech.h"

// Sets default values for this component's properties
UMechAimComponent::UMechAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UMechAimComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerMech = Cast<AMech>(GetOwner());
	if (!OwnerMech)
	{
		UE_LOG(LogMech, Error, TEXT("UMechAimComponent: Owner is not a mech!"));
		return;
	}
	if (!OwnerMech->Implements<UWeaponizedInterface>())
	{
		UE_LOG(LogMech, Error, TEXT("UMechAimComponent: Mech does not implement the IWeaponizedInterface!"));
		return;
	}

	// Initialize if the mech is fully initialized. Otherwise wait for it to be initialized.
	if (OwnerMech->IsInitialized())
	{
		HandleMechInitialized();
	}
	else
	{
		OwnerMech->OnInitialized.AddDynamic(this, &UMechAimComponent::HandleMechInitialized);
	}
}

// Called when the game starts
void UMechAimComponent::BeginPlay()
{
	Super::BeginPlay();
}

FVector UMechAimComponent::GetAimTargetLocation()
{
	// stub
	return FVector::ZeroVector;
}

// Called every frame
void UMechAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMechAimComponent::HandleMechInitialized()
{
	// todo
	/*
	TArray<AWeapon*> Weapons;
	IWeaponizedInterface::Execute_GetWeapons(OwnerMech, Weapons);

	// TODO: Retrieve information required.
	for (const AWeapon* Weapon : Weapons)
	{

	}
	*/
}