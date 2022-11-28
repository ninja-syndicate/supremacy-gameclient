// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechAimComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Mechs/Mech.h"
#include "Weapons/Weapon.h"
#include "Core/Game/SupremacyTypes.h"
#include "Core/Gameplay/GameplayTags.h"
#include "AI/CombatAgentInterface.h"

// Sets default values for this component's properties
UMechAimComponent::UMechAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UMechAimComponent::BeginPlay()
{
	Super::BeginPlay();

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
	bIsInitialized = true;
}

// Called every frame
void UMechAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// @todo - support arced weapons.
	// @todo - Use vector spring interp to get natural spring transition to the aim location.
	FVector TargetLocation = GetTargetLocation();

	if (bEnableSpringAimInterpolation)
	{
		CurrentAimLocation = UKismetMathLibrary::VectorSpringInterp(
			CurrentAimLocation, TargetLocation, VectorSpringState, SpringStiffness, SpringCriticalDampeningFactor, DeltaTime);
	}


	// FVector AimLocation = UKismetMathLibrary::VInterpTo_Constant(CurrentAimLocation, TargetLocation, DeltaTime, );
	// CurrentAimLocation = AimLocation;


}

FVector UMechAimComponent::GetAimLocation()
{
	return CurrentAimLocation;
}

/*
void UMechAimComponent::GetSpringCameraViewpoint()
{
	// TODO: implementation
}
*/

void UMechAimComponent::GetCameraViewpoint(FVector& OutCameraLocation, FRotator& OutCameraRotation)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (!CameraManager) return;

	OutCameraLocation = CameraManager->GetCameraLocation();
	OutCameraRotation = CameraManager->GetCameraRotation();
}

FVector UMechAimComponent::GetTargetLocation()
{
	// Return zero vector if not initialized.
	if (!bIsInitialized) return FVector::ZeroVector;

	// If the mech is not controlled, just fallback to the base aim rotation.
	if (!OwnerMech->IsPawnControlled()) 
		return GetBaseAimLocation();

	// For player controlled mechs.
	if (OwnerMech->IsPlayerControlled())
		return GetPlayerAimLocation();

	// For AI-controlled mechs.
	if (OwnerMech->IsBotControlled())
	{
		if (!OwnerMech->GetController()->Implements<UCombatAgentInterface>()) return FVector::ZeroVector;

		ICombatAgentInterface* CombatAgent = Cast<ICombatAgentInterface>(OwnerMech->GetController());
		if (CombatAgent) return FVector::ZeroVector;

		// Use the current target's location if present and fallback to base aim location otherwise.
		AActor* CurrentTarget = CombatAgent->GetCurrentTarget();
		return CurrentTarget ? CurrentTarget->GetActorLocation() : GetBaseAimLocation();
	}
	return FVector::ZeroVector;
}

FVector UMechAimComponent::GetBaseAimLocation()
{
	const FRotator AimRotation = OwnerMech->GetBaseAimRotation();
	const FVector AimLocation = OwnerMech->GetActorLocation() + AimRotation.Vector() * TraceDistance;
	return AimLocation;
}

FVector UMechAimComponent::GetPlayerAimLocation()
{
	// @todo - optimize this.
	TArray<AWeapon*> MechWeapons;
	IWeaponizedInterface::Execute_GetWeapons(OwnerMech, MechWeapons);

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	for (AWeapon* Weapon : MechWeapons)
	{
		QueryParams.AddIgnoredActor(Weapon);
	}

	FVector TraceStartLocation = CameraManager->GetCameraLocation();
	FVector TraceEndLocation = TraceStartLocation + CameraManager->GetActorForwardVector() * TraceDistance;
	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Visibility, QueryParams);

	return bIsHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
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