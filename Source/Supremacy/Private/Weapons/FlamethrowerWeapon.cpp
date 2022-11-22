// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FlamethrowerWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/BoxComponent.h"

#include "Core/Game/SupremacyTypes.h"
#include "Core/Game/SupremacyGameInstance.h"
#include "Core/Damage/Damager.h"

AFlamethrowerWeapon::AFlamethrowerWeapon() : Super()
{
	// Create default flamethrower static mesh component to be set by blueprints.
	// Assumes that every flamethrower will have some sort of static mesh.
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetCanEverAffectNavigation(false);

	Damager = CreateDefaultSubobject<UDamager>(TEXT("Damager"));

	// Every flamethrower can be used as a melee weapon.
	MeleeBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeBoxComponent"));

	// Create default flame stream niagara component and turn it off by default.
	FlameStreamNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FlameStreamNiagaraComponent"));
	FlameStreamNiagaraComp->SetAutoActivate(false);
	FlameStreamNiagaraComp->SetAutoDestroy(false);
	FlameStreamNiagaraComp->SetVisibility(false);

	// Prevent niagara effect getting scaled when static mesh comp gets scaled as it will look bad.
	FlameStreamNiagaraComp->SetAbsolute(false, false, true);

	// Setup component hierarchy.
	StaticMeshComp->SetupAttachment(RootComponent);
	FlameStreamNiagaraComp->SetupAttachment(StaticMeshComp, BarrelSocketName);
	MeleeBoxComp->SetupAttachment(StaticMeshComp);
}

void AFlamethrowerWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Check for the niagara asset. This needs to be set from the blueprint.
	if (!FlameStreamNiagaraComp->GetAsset())
	{
		UE_LOG(LogWeapon, Warning, TEXT("AFlamethrowerWeapon: Flamethrower is missing the niagara asset. Please set one."));
		return;
	}

	// Check instigator. TODO: Move this to AWeapon?
	if (!GetInstigator())
	{
		UE_LOG(LogWeapon, Error, TEXT("AFlamethrowerWeapon: Need an instigator to associate this weapon to."));
		return;
	}

	// Get all the child actors and include them as part of actors to ignore.
	GetInstigator()->GetAllChildActors(ActorsToIgnore);
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetInstigator());
	// @todo - include shield.

	// Check rate of fire.
	if (Struct.Rate_Of_Fire <= 0)
	{
		UE_LOG(LogWeapon, Error, TEXT("AFlamethrowerWeapon: The rate of fire must be positive."));
		return;
	}
	// Calculate the scan interval from the rate of fire.
	ScanTickInterval = 60 / Struct.Rate_Of_Fire;

	// Get the static mesh component of the weapon. TODO: Probably make a GetMainStaticMesh() function that retreives the appropriate one in AWeapon.
	StaticMeshComp = FindComponentByClass<UStaticMeshComponent>();
	if (!IsValid(StaticMeshComp))
	{
		UE_LOG(LogWeapon, Warning, TEXT("AFlamethrowerWeapon: The weapon is missing static mesh component!"));
		return;
	}

	// Get the game instance to figure out the nonflammable surface types.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	USupremacyGameInstance* SupremacyGameInstance = Cast<USupremacyGameInstance>(GameInstance);
	if (!SupremacyGameInstance)
	{
		UE_LOG(LogWeapon, Warning, TEXT("AFlamethrowerWeapon: The current game instance is not USupremacyGameInstance. This will result in surface types being ignored."));
		return;
	}
	NonflammableSurfaceTypes = SupremacyGameInstance->GetNonflammableSurfaceTypes();

	Damager->SetDamageByWeaponStruct(Struct);
	bIsInitialized = true;
}

void AFlamethrowerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsInitialized) return;

	// @todo - Gradually scale the line trace distance based on the charge time to take account of vfx length.
	if (!bIsTriggered)
	{
		CurrentChargeTime = FMath::Max(0, CurrentChargeTime - DeltaTime);
	}
	else
	{
		CurrentChargeTime += DeltaTime;
		if (CurrentChargeTime >= ScanTickInterval)
		{
			CurrentChargeTime -= ScanTickInterval;
			HitScan();
		}
	}
}

void AFlamethrowerWeapon::Trigger_Implementation()
{
	Super::Trigger_Implementation();

	if (!bIsInitialized) return;

	// Activate the niagara vfx and visibility.
	if (!FlameStreamNiagaraComp->IsActive())
	{
		FlameStreamNiagaraComp->Activate(true);
	}
	if (!FlameStreamNiagaraComp->IsVisible())
	{
		FlameStreamNiagaraComp->SetVisibility(true);
	}
}

void AFlamethrowerWeapon::Release_Implementation()
{
	Super::Release_Implementation();

	if (!bIsInitialized) return;

	// If already not active, don't do anything.
	if (!FlameStreamNiagaraComp->IsActive()) return;

	// Turn off visibility.
	if (FlameStreamNiagaraComp->IsVisible())
	{
		FlameStreamNiagaraComp->SetVisibility(false);
	}
}

void AFlamethrowerWeapon::HitScan()
{
	const float Spread = Struct.Spread;
	const float TraceDist = Struct.Damage_Falloff;
	const FTransform& SocketTransform = StaticMeshComp->GetSocketTransform(BarrelSocketName);

	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector TraceEnd = TraceStart + UKismetMathLibrary::RandomPointInBoundingBox(
		SocketTransform.GetRotation().GetForwardVector() * TraceDist, FVector{ Spread });

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	// @todo: change to multi trace
	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, TraceStart, TraceEnd, TraceChannel_Damageable, QueryParams);

	AActor* HitActor = nullptr;
	if (bIsHit)
	{
		HitActor = HitResult.GetActor();
		// @todo: damage the actor
	}

	// Fail-fast on invalid hits.
	if (!HitResult.GetActor()) return;
	if (!HitResult.PhysMaterial.IsValid()) return;

	ApplyBurnDecal(HitResult);
	ApplyBurning(HitResult);
}

void AFlamethrowerWeapon::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffset)
{
	// @todo - optimizaiton to ignore some stuff.

	// @todo - find centroid/random of the particles, trace and see its surface type if it can be burned.
	UE_LOG(LogWeapon, Warning, TEXT("Received data. Count: %d"), Data.Num());
}

void AFlamethrowerWeapon::ApplyBurnDecal_Implementation(const FHitResult& HitResult)
{
	// @todo implementation
	if (!BurnDecalMat) return;

	// Check if it can burned.
	EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
	if (NonflammableSurfaceTypes.Contains(SurfaceType)) return;


}

void AFlamethrowerWeapon::ApplyBurning_Implementation(const FHitResult& HitResult)
{
	// @todo implementation
	if (!BurningNiagaraComp) return;

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