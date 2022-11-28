// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/MeleeCapabilityComponent.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISenseEvent_Hearing.h"
#include "NiagaraFunctionLibrary.h"

#include "Weapons/Weapon.h"
#include "Weapons/Components/WeaponAmmunitionComponent.h"
#include "Core/Damage/Damageable.h"
#include "Core/Gameplay/GameplayTags.h"

// Sets default values for this component's properties
UMeleeCapabilityComponent::UMeleeCapabilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UMeleeCapabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// Feature: Use the weapon collision instead of box collision if required.
	if (!bUseBoxComp)
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Not using box component is currently not supported."));
		return;
	}

	// Check if it's valid owner.
	if (!GetOwner())
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Owner is invalid!"));
		return;
	}
	// Check if it has valid instigator to associate damage with.
	if (!GetOwner()->GetInstigator())
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Invalid instigator!"));
		return;
	}

	// Check for melee box comps.
	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(UBoxComponent::StaticClass(), MeleeBoxCompTagName);
	if (Components.Num() == 0)
	{
		UE_LOG(LogWeapon, Error, TEXT("UMeleeCapabilityComponent: Needs a UBoxComponent to work."));
		return;
	}

	if (Components.Num() > 1)
	{
		UE_LOG(LogWeapon, Warning, TEXT("UMeleeCapabilityComponent: Multiple melee box components aren't supported yet. Using the first one as a fallback."));
	}
	// Bind events.
	MeleeBoxComp = Cast<UBoxComponent>(Components[0]);
	MeleeBoxComp.Get()->OnComponentBeginOverlap.AddDynamic(this, &UMeleeCapabilityComponent::OnMeleeBoxBeginOverlap);
	MeleeBoxComp.Get()->OnComponentEndOverlap.AddDynamic(this, &UMeleeCapabilityComponent::OnMeleeBoxEndOverlap);

	// Get the ammo comp if it has one and use that to determine when to switch poses.
	UWeaponAmmunitionComponent* AmmoComp = GetOwner()->FindComponentByClass<UWeaponAmmunitionComponent>();
	if (!AmmoComp)
	{
		// For now, if it has no ammo comp, always melee. TODO: Provide options.
		bSwitchToMeleePose = true;
	}
	else
	{
		bSwitchToMeleePose = !AmmoComp->HasAmmo();
		AmmoComp->OnAmmoChanged.AddDynamic(this, &UMeleeCapabilityComponent::HandleAmmoChanged);
	}

	// @todo - fix up melee box scale.
}

void UMeleeCapabilityComponent::HandleAmmoChanged(int CurrentAmmo)
{
	bSwitchToMeleePose = CurrentAmmo <= 0;
}

bool UMeleeCapabilityComponent::TriggerMelee_Implementation()
{
	// For now, the main logic will be implemented in the blueprints.
	return true;
}

void UMeleeCapabilityComponent::OnMeleeBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APawn* Instigator = GetOwner()->GetInstigator();

	// Ignore if it somehow ended up overlapping the instigator.
	if (OtherActor == Instigator) return;
	if (OtherActor->GetInstigator() == Instigator) return;

	// Ignore if already overlapped.
	if (OverlappingActors.Contains(OtherActor)) return;

	bool bHitDamageable = false;
	bool bHitShield = false;
	IGameplayTagAssetInterface* GameplayInterface = Cast<IGameplayTagAssetInterface>(OtherActor);
	if (GameplayInterface)
	{
		bHitDamageable = GameplayInterface->HasMatchingGameplayTag(TAG_Damageable);
		bHitShield = GameplayInterface->HasMatchingGameplayTag(TAG_Shield);
	}
	USoundBase* SoundToPlay = bHitDamageable ? DamageableHitSound : NormalHitSound;

	OverlappingActors.Add(OtherActor);

	// Spawn vfx and play sound at that location.
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		HitEffect,
		SweepResult.ImpactPoint,
		UKismetMathLibrary::Conv_VectorToRotator(SweepResult.ImpactNormal));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, SweepResult.ImpactPoint, 1.0f, 1.0f, 0.0f, SoundAttenuation);

	// check team and damage the actor
	OtherActor;
	Instigator;

	// Report noise event for AI.
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), SweepResult.ImpactPoint, 1.0f, Instigator, MaxHitNoiseRange, AWeapon::GetTagName());
}

void UMeleeCapabilityComponent::OnMeleeBoxEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	const APawn* Instigator = GetOwner()->GetInstigator();

	// Ignore if it somehow ended up overlapping the instigator.
	if (OtherActor == Instigator) return;
	if (OtherActor->GetInstigator() == Instigator) return;

	// @todo - If animation is on-going, put into (to-be removed actor list)
	// if (...)
	// else
	OverlappingActors.Remove(OtherActor);
}

// Called every frame
void UMeleeCapabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}