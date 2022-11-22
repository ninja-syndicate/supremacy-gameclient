// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animation/MechAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"

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
		MechOwner->OnInitialized.AddDynamic(this, &UMechAnimInstance::HandleMechInitialized);
	}
	bIsInitialized = true;
}

void UMechAnimInstance::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);

	if (!bIsInitialized) return;

	PreVelocity = MechOwner->GetVelocity();
	PreRotation = MechOwner->GetActorRotation();
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
}

void UMechAnimInstance::UpdateLocomotion_Implementation(float DeltaSeconds)
{
	// Only perform thread-safe operations here.
	Speed = PreVelocity.Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(PreVelocity, PreRotation);
}

void UMechAnimInstance::HandleMechInitialized_Implementation()
{
	// Currently, this is implemented in animation blueprints.
}