// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/WeaponScaleComponent.h"

#include "GameplayTagAssetInterface.h"

#include "Core/Gameplay/GameplayTags.h"
#include "Logger/SupremacyLogTypes.h"
#include "Weapons/WeaponizedInterface.h"

// Sets default values for this component's properties
UWeaponScaleComponent::UWeaponScaleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UWeaponScaleComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Invalid owner."));
		return;
	}

	IGameplayTagAssetInterface* GameplayTagInterface = Cast<IGameplayTagAssetInterface>(GetOwner());
	if (!GameplayTagInterface || !GameplayTagInterface->HasMatchingGameplayTag(TAG_Weapon))
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: The instigator does not implement IGameplayTagAssetInterface or missing the tag."));
		return;
	}

	APawn* Instigator = GetOwner()->GetInstigator();
	if (!Instigator)
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Invalid instigator."));
		return;
	}

	if (!Instigator->Implements<UWeaponizedInterface>())
	{
		UE_LOG(LogComponent, Error, TEXT("UWeaponScaleComponent: Instigator does not imlpement UWeaponizedInterface!"));
		return;
	}

	UStaticMeshComponent* StaticMeshComp = nullptr;
	TArray<UActorComponent*> Comps = GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), MainStaticMeshTagName);
	if (Comps.IsEmpty())
	{
		// If no components with the tag "Main", then fallback to the first static mesh component.
		// If there isn't one, nothing needs to be scaled.
		StaticMeshComp = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
		if (!StaticMeshComp) return;
	}
	else
	{
		// There should be only one main static mesh component so cast the first one.
		StaticMeshComp = Cast<UStaticMeshComponent>(Comps[0]);
	}

	// NOTE: To avoid weird looking niagara effects after scaling, the scale mode of the niagara effects needs
	// to be Absolute Scale if it is attached to the static mesh component. And change the niagara effect
	// appropriately.
	const float WeaponBaseScale = IWeaponizedInterface::Execute_GetWeaponBaseScale(Instigator);
	const FVector NewRelativeScale = StaticMeshComp->GetRelativeScale3D() * WeaponBaseScale;
	StaticMeshComp->SetRelativeScale3D(NewRelativeScale);

	//@todo - listen for the scale change and re-size it.
}

// Called every frame
void UWeaponScaleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
