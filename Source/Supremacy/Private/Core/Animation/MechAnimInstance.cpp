// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animation/MechAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Mechs/Mech.h"

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
}

void UMechAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMechAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!bIsInitialized) return;

	UpdateLocomotion(DeltaSeconds);
	UpdateUpperBody(DeltaSeconds);
}

void UMechAnimInstance::UpdateLocomotion_Implementation(float DeltaSeconds)
{
	// Only perform thread-safe operations here.
	Speed = PreVelocity.Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(PreVelocity, PreRotation);
}

void UMechAnimInstance::UpdateUpperBody_Implementation(float DeltaSeconds)
{
	const FRotator TargetUpperBodyRot = (PreLookRotation - PreRotation).GetNormalized();
	UpperBodyRot = UKismetMathLibrary::RInterpTo_Constant(UpperBodyRot, TargetUpperBodyRot, DeltaSeconds, UpperBodyTurnRate);
}

void UMechAnimInstance::HandleMechInitialized_Implementation()
{
	// Currently, this is implemented in animation blueprints.
}

void UMechAnimInstance::HandleWeaponEquipped_Implementation(AWeapon* Weapon)
{
	// Currently, this is implemented in animation blueprints.
}