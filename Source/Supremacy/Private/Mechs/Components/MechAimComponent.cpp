// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechs/Components/MechAimComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Mechs/Mech.h"
#include "Weapons/Weapon.h"
#include "Core/Game/SupremacyFunctionLibrary.h"
#include "Core/Gameplay/GameplayTags.h"
#include "AI/CombatAgentInterface.h"

// Sets default values for this component's properties
UMechAimComponent::UMechAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	// Return if not initialized yet.
	if (!bIsInitialized) return;

	// @todo - support arced weapons.
	// @todo - Use vector spring interp to get natural spring transition to the aim location.
	/*
	FVector TargetLocation = GetTargetLocation();

	if (bEnableSpringAimInterpolation)
	{
		CurrentAimLocation = UKismetMathLibrary::VectorSpringInterp(
			CurrentAimLocation, 
			TargetLocation, 
			VectorSpringState, 
			SpringStiffness, 
			SpringCriticalDampeningFactor, 
			DeltaTime, 
			1.0f, 
			1.0f);
	}
	else 
	{
		// For now, directly snap to the target point for testing.
		CurrentAimLocation = TargetLocation;
	}
	*/
}

FVector UMechAimComponent::GetAimLocation() const
{
	return CurrentAimTransform.GetTranslation();
	// return CurrentAimLocation;
}

void UMechAimComponent::GetCameraViewpoint(FVector& OutCameraLocation, FRotator& OutCameraRotation)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (!CameraManager) return;

	OutCameraLocation = CameraManager->GetCameraLocation();
	OutCameraRotation = CameraManager->GetCameraRotation();
}

FVector UMechAimComponent::GetTargetLocation()
{
	// If the mech is not controlled, just fallback to the base aim rotation.
	if (!OwnerMech->IsPawnControlled()) 
		return GetBaseAimLocation();

	// For player controlled mechs.
	if (OwnerMech->IsPlayerControlled())
	{
		const FTransform AimTargetTransform = GetPlayerAimTargetTransform();
		DrawDebugLine(GetWorld(), AimTargetTransform.GetTranslation(), AimTargetTransform.GetTranslation() + AimTargetTransform.GetUnitAxis(EAxis::X) * 4096, FColor(0, 0, 255), true, -1, 0, 12.33f);
		return AimTargetTransform.GetTranslation() + AimTargetTransform.GetUnitAxis(EAxis::X) * FocalDistance;
	}

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
	const FVector AimLocation = OwnerMech->GetActorLocation() + AimRotation.Vector().GetSafeNormal() * FocalDistance;
	return AimLocation;
}

FTransform UMechAimComponent::GetPlayerAimTargetTransform()
{
	const AController* Controller = OwnerMech->GetController();
	const FVector PawnLocation = OwnerMech->GetActorLocation();
	const FQuat PawnQuat = OwnerMech->GetActorQuat();

	// Get the player camera location and rotation from the controller.
	FVector CameraLocation;
	FRotator CameraRotation;
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	}
	// @todo - pathing for AI.

	// const float FocalDistance = FVector::Dist(CameraLocation, PawnLocation);

	// Get the aim direction from the camera and focal location.
	FVector AimDirection = CameraRotation.Vector().GetSafeNormal();
	FVector FocalLocation = CameraLocation + AimDirection * FocalDistance;
	DrawDebugLine(GetWorld(), CameraLocation, FocalLocation, FColor(0, 255, 0), true, -1, 0, 12.33f);

	if (PlayerController)
	{
		// @todo test focal distance, and linetrace testing, and optimal range.
		// @todo actually get weapon location.
		const FVector WeaponLocation = PawnLocation;

		CameraLocation = FocalLocation + ((WeaponLocation - FocalLocation) | AimDirection) * AimDirection;
		FocalLocation = CameraLocation + (AimDirection * FocalDistance);
		DrawDebugLine(GetWorld(), CameraLocation, FocalLocation, FColor(255, 0, 0), true, -1, 0, 12.33f);
	}
	// @todo handle for AI
	FVector SourceLocation = PawnLocation;
	const FTransform AimTargetTransform((FocalLocation - SourceLocation).Rotation(), SourceLocation);

	return AimTargetTransform;


	// @todo - optimize this.
	/*
	TArray<AWeapon*> MechWeapons;
	IWeaponizedInterface::Execute_GetWeapons(OwnerMech, MechWeapons);

	FVector CameraLocation;
	FRotator CameraRotation;
	GetCameraViewpoint(CameraLocation, CameraRotation);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	for (AWeapon* Weapon : MechWeapons)
	{
		QueryParams.AddIgnoredActor(Weapon);
	}

	FVector TraceStartLocation = CameraLocation;
	FVector TraceEndLocation = TraceStartLocation + UKismetMathLibrary::GetForwardVector(CameraRotation) * TraceDistance;
	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Visibility, QueryParams);

	return bIsHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
	*/
}

void UMechAimComponent::HandleMechInitialized()
{
	// @todo - probably make independent of mech initialization state.
	/*
	FGameplayTagContainer FireableWeapon;
	FireableWeapon.AddTag(TAG_Weapon);
	FireableWeapon.AddTag(TAG_Weapon_Fireable);

	TArray<AWeapon*> Weapons;
	IWeaponizedInterface::Execute_GetWeapons(OwnerMech, Weapons);

	for (AWeapon* Weapon : Weapons)
	{
		IGameplayTagAssetInterface* GameplayTagInterface = Cast<IGameplayTagAssetInterface>(Weapon);
		if (!GameplayTagInterface) continue;

		const bool bIsFireableWeapon = GameplayTagInterface->HasAllMatchingGameplayTags(FireableWeapon);
		if (!bIsFireableWeapon) continue;

		// TODO:
	}
	*/
}