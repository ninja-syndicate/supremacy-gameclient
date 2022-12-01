// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animation/MechAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Mechs/Mech.h"
#include "Weapons/Weapon.h"
#include "Weapons/Components/WeaponAimComponent.h"
#include "Core/Gameplay/GameplayTags.h"

UMechAnimInstance::UMechAnimInstance() : Super()
{
}

void UMechAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if (!TryGetPawnOwner())
	{
		UE_LOG(LogAnimation, Error, TEXT("UMechAnimInstance: Could not get the pawn owner!"));
		return;
	}

	MechOwner = Cast<AMech>(TryGetPawnOwner());
	if (!MechOwner)
	{
		UE_LOG(LogAnimation, Error, TEXT("UMechAnimInstance: Owner is not a mech!"));
		return;
	}

	MechMesh = GetOwningComponent();
	if (!MechMesh)
	{
		UE_LOG(LogAnimation, Error, TEXT("UMechAnimInstance: Owner is missing skeletal mesh!"));
		return;
	}

	const int NumSlots = SlotBoneMapping.Num();
	AimComponents.SetNum(NumSlots);
	AimLocations.SetNum(NumSlots);
	
	// Initialize after mech is fully initialized.
	if (MechOwner->IsInitialized())
	{
		HandleMechInitialized();
	}
	else
	{
		MechOwner->OnWeaponEquipped.AddDynamic(this, &UMechAnimInstance::HandleWeaponEquipped);
		//MechOwner->OnInitialized.AddDynamic(this, &UMechAnimInstance::HandleMechInitialized);
	}

	// @todo - move this to a function
	if (bCustomUpperBodyTurnRate)
	{
		bIsInitialized = true;
		return;
	}

	UCharacterMovementComponent* MoveComp = MechOwner->FindComponentByClass<UCharacterMovementComponent>();
	if (!MoveComp)
	{
		UE_LOG(LogAnimation, Error, TEXT("UMechAnimInstance: The pawn owner is missing character movement component!"));
		return;
	}
	else
	{
		UpperBodyTurnRate = MoveComp->RotationRate.Yaw;
	}
	bIsInitialized = true;
}

void UMechAnimInstance::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);

	if (!bIsInitialized) return;

	PreVelocity = MechOwner->GetVelocity();
	PreRotation = MechOwner->GetActorRotation();
	PreLookRotation = MechOwner->GetControlRotation();

	for (int i = 0; i < SlotBoneMapping.Num(); ++i)
	{
		if (!AimComponents[i]) continue;

		FTransform BarrelTransform = AimComponents[i]->GetBarrelTransform();

		// Get the corresponding bone to offset for this weapon slot.
		const FName BoneName = SlotBoneMapping[i];

		// @todo - validate logic;
		FVector BarrelUpVector = BarrelTransform.GetRotation().GetUpVector();
		FVector AimBonePitchLocation = MechMesh->GetSocketLocation(BoneName);
		FVector Delta = BarrelUpVector * (AimBonePitchLocation - BarrelTransform.GetLocation()).Dot(BarrelUpVector);

		// DrawDebugLine(GetWorld(), AimBonePitchLocation, AimBonePitchLocation + Delta, FColor::Black, false, 0.5, 0, 12.0f);
		AimLocations[i] = AimComponents[i]->GetAimLocation() + Delta;
	}
}

void UMechAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMechAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!bIsInitialized) return;

	// Only perform thread-safe operations here.
	UpdateLocomotion(DeltaSeconds);
	UpdateUpperBody(DeltaSeconds);
	UpdateAimLocation(DeltaSeconds);
}

void UMechAnimInstance::UpdateLocomotion_Implementation(float DeltaSeconds)
{
	Speed = PreVelocity.Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(PreVelocity, PreRotation);
}

void UMechAnimInstance::UpdateUpperBody_Implementation(float DeltaSeconds)
{
	const FRotator TargetUpperBodyRot = (PreLookRotation - PreRotation).GetNormalized();
	UpperBodyRot = UKismetMathLibrary::RInterpTo_Constant(UpperBodyRot, TargetUpperBodyRot, DeltaSeconds, UpperBodyTurnRate);
}

void UMechAnimInstance::UpdateAimLocation_Implementation(float DeltaSeconds)
{
	// @todo - move some of pre stuff to here.
}

void UMechAnimInstance::HandleMechInitialized_Implementation()
{
	// Currently, this is implemented in animation blueprints.
}

void UMechAnimInstance::HandleWeaponEquipped_Implementation(AWeapon* Weapon)
{
	// Check for the gameplay tag interface.
	IGameplayTagAssetInterface* GameplayTagInterface = Cast<IGameplayTagAssetInterface>(Weapon);
	if (!GameplayTagInterface) return;

	// For now, the weapon needs to be fireable and primary to require any aiming in the anim BP.
	FGameplayTagContainer TagRequirements;
	TagRequirements.AddTag(TAG_Weapon);
	TagRequirements.AddTag(TAG_Weapon_Fireable);
	TagRequirements.AddTag(TAG_Weapon_Primary);

	if (!GameplayTagInterface->HasAllMatchingGameplayTags(TagRequirements)) return;

	const int WeaponSlot = Weapon->Struct.Socket_Index;
	if (WeaponSlot < 0 || WeaponSlot >= SlotBoneMapping.Num())
	{
		UE_LOG(LogAnimation, Error, TEXT("UMechAnimInstance: Invalid weapon slot index."));
		return;
	}
	AimComponents[WeaponSlot] = Weapon->FindComponentByClass<UWeaponAimComponent>();
}

TArray<FName> UMechAnimInstance::GetSocketNames()
{
	if (!GetOwningComponent()) return TArray<FName>();

	return GetOwningComponent()->GetAllSocketNames();
}