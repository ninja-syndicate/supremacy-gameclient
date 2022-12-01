// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/WeaponAimComponent.h"

#include "Weapons/Weapon.h"
#include "Weapons/Constants.h"
#include "Logger/SupremacyLogTypes.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UWeaponAimComponent::UWeaponAimComponent()
{
	// This component needs tick.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UWeaponAimComponent::BeginPlay()
{
	Super::BeginPlay();

	Weapon = Cast<AWeapon>(GetOwner());
	if (!Weapon)
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponAimComponent: Owner is not a weapon!"));
		return;
	}

	OwnerPawn = Weapon->GetInstigator();
	if (!OwnerPawn)
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponAimComponent: Invalid instigator!"));
		return;
	}

	// Get the static mesh comp with the barrel.
	TArray<UActorComponent*> ActorComps;
	ActorComps = Weapon->GetComponentsByTag(UStaticMeshComponent::StaticClass(), WeaponConstants::BarrelStaticMeshTagName);
	if (ActorComps.IsEmpty())
	{
		WeaponBarrelStaticMesh = Weapon->FindComponentByClass<UStaticMeshComponent>();

		// Currently, the weapon with no static mesh is not supported.
		if (!WeaponBarrelStaticMesh)
		{
			UE_LOG(LogComponent, Warning, TEXT("UWeaponAimComponent: Missing static mesh. Won't do aiming support."));
			return;
		}
	}
	else
	{
		// Get the first static mesh comp (there should be only one).
		WeaponBarrelStaticMesh = Cast<UStaticMeshComponent>(ActorComps[0]);
	}
	bIsInitialized = true;
}

// Called every frame
void UWeaponAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsInitialized) return;

	if (OwnerPawn->IsPlayerControlled())
	{
		AimLocation = GetPlayerAimTargetTransform();
		BarrelTransform = WeaponBarrelStaticMesh->GetSocketTransform(WeaponConstants::BarrelSocketName);
	}
}

FVector UWeaponAimComponent::GetAimLocation() const
{
	return AimLocation;
}

FTransform UWeaponAimComponent::GetBarrelTransform() const
{
	return BarrelTransform;
}

FVector UWeaponAimComponent::GetPlayerAimTargetTransform()
{
	const AController* Controller = OwnerPawn->GetController();
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);

	// Get the weapon barrel world-space transform.
	const FVector BarrelLocation = WeaponBarrelStaticMesh->GetSocketLocation(WeaponConstants::BarrelSocketName);

	// Get the player camera location and rotation from the controller.
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// @todo - check for camera/weapon collision
	// Perform the trace along the camera location and rotation to find the aim location.
	const FVector CameraAimLocation = Trace(CameraLocation, CameraRotation, BarrelLocation);
	return CameraAimLocation;
}

FVector UWeaponAimComponent::Trace(const FVector& CameraLocation, const FRotator& CameraRotation, const FVector& BarrelLocation)
{
	// Get the camera's forward and project the camera location to the camera plane to get the weapon barrel trace start location.
	FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(CameraRotation);
	FVector TraceStartLocation = UKismetMathLibrary::ProjectPointOnToPlane(CameraLocation, BarrelLocation, CameraForwardVector);
	FVector TraceEndLocation = TraceStartLocation + CameraForwardVector * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(GetOwner()->GetInstigator());
	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Visibility, QueryParams);

	// @todo - For some short-range weapon, use the optimal range instead.
	const FVector FocalLocation = TraceStartLocation + CameraForwardVector * FocalDistance;
	return bIsHit ? HitResult.ImpactPoint : FocalLocation;
}