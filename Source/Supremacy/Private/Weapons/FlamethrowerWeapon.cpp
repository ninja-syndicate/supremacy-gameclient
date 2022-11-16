// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FlamethrowerWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NiagaraFunctionLibrary.h"

#include "Core/Game/SupremacyTypes.h"

void AFlamethrowerWeapon::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp = FindComponentByClass<UStaticMeshComponent>();
	if (!IsValid(StaticMeshComp))
	{
		UE_LOG(LogTemp, Error, TEXT("AFlamethrowerWeapon: The weapon is missing static mesh component!"));
		return;
	}
}

void AFlamethrowerWeapon::HitScan()
{
	// Check for is firing?
	if (!bIsTriggered) return;

	const float Spread = Struct.Spread;
	const float TraceDist = Struct.Damage_Falloff;
	const FTransform& SocketTransform = StaticMeshComp->GetSocketTransform(BarrelSocketName);

	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector TraceEnd = TraceStart + UKismetMathLibrary::RandomPointInBoundingBox(
		SocketTransform.GetRotation().GetForwardVector() * TraceDist, FVector{ Spread });

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	//QueryParams.

	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, TraceStart, TraceEnd, TraceChannel_Damageable, QueryParams);

	AActor* HitActor = nullptr;
	if (bIsHit)
	{
		HitActor = HitResult.GetActor();

	}
	ApplyBurnDecal(HitResult);
	ApplyBurning(HitResult);
}

void AFlamethrowerWeapon::ApplyBurnDecal_Implementation(const FHitResult& HitResult)
{
	// @todo implementation
	if (!BurnDecalMat) return;
	if (!HitResult.PhysMaterial.IsValid()) return;

	// Check if it can burned.
	EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
	if (NonflammableSurfaceTypes.Contains(SurfaceType)) return;


}

void AFlamethrowerWeapon::ApplyBurning_Implementation(const FHitResult& HitResult)
{
	// @todo implementation
	if (!BurningNiagaraComp) return;
	if (!HitResult.GetActor()) return;
	if (!HitResult.PhysMaterial.IsValid()) return;

	// There should be hit component if the actor is valid, but do a safe check.
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	if (!HitComponent) return;

	// Check if it can burned.
	EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
	if (NonflammableSurfaceTypes.Contains(SurfaceType)) return;

	FName HitBoneName = HitResult.BoneName;
	FVector HitLocation = HitResult.ImpactPoint;

	/*
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		BurningNiagaraComp,
		HitComponent,
		HitBoneName,
		
		
		
		false);
	*/

}