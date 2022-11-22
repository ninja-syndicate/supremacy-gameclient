// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

#include "Net/UnrealNetwork.h"
#include "Engine/AssetManager.h"

#include "Core/Gameplay/GameplayTagFunctionLibrary.h"
#include "BlueprintGameplayTagLibrary.h"

DEFINE_LOG_CATEGORY(LogWeapon);

// Sets default values
AWeapon::AWeapon() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!GetInstigator())
	{
		UE_LOG(LogWeapon, Error, TEXT("AWeapon: Instigator is invalid."));
		return;
	}

	// Append the init gameplay tags into the main gameplay tag container.
	UBlueprintGameplayTagLibrary::AppendGameplayTagContainers(
		GameplayTagContainer, UGameplayTagFunctionLibrary::GetAllTags(InitGameplayTagContainer));

	TArray<USceneComponent*> ChildrenComps;
	RootComponent->GetChildrenComponents(true, ChildrenComps);

	// Ignore this weapon's components when moving. (This may not be required?)
	for (USceneComponent* Comp : ChildrenComps)
	{
		UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(Comp);
		if (!PrimitiveComp) return;

		PrimitiveComp->IgnoreActorWhenMoving(this, true);
		PrimitiveComp->IgnoreActorWhenMoving(GetInstigator(), true);
	}
}

// Called every frame
void AWeapon::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 

	DOREPLIFETIME(AWeapon, GameplayTagContainer);
	DOREPLIFETIME(AWeapon, Struct);
	DOREPLIFETIME_CONDITION(AWeapon, InitGameplayTagContainer, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AWeapon, TargetLocation, COND_InitialOnly);
}


void AWeapon::Initialize_Implementation()
{
	// @todo implementation
}

void AWeapon::Trigger_Implementation()
{
	// IMPORTANT: Currently, BP_Weapon does not call Parent's Trigger/Release call in its overriden functions. 
	// Which means any code you place here will not be executed unless a derived weapon is implemented in C++. 
	// Until BP_Weapon's trigger/release functions are fully ported to here, do not call parent's trigger/release in BP_Weapon.

	if (!bIsTriggered)
	{
		bIsTriggered = true;

		// Only broadcast when the trigger state changed.
		OnTriggerStateChanged.Broadcast(bIsTriggered);
	}
}

void AWeapon::Release_Implementation()
{
	// IMPORATNT: Read Trigger_Implementation comment.

	if (bIsTriggered)
	{
		bIsTriggered = false;

		// Only broadcast when the trigger state changed.
		OnTriggerStateChanged.Broadcast(bIsTriggered);
	}
}

bool AWeapon::IsInitialized() const
{
	return bIsInitialized;
}

bool AWeapon::IsTriggered() const
{
	return bIsTriggered;
}

bool AWeapon::CanFriendlyFire() const
{
	return bEnableFriendlyFire;
}

void AWeapon::SetFriendlyFire(bool Enable)
{
	bEnableFriendlyFire = Enable;
}

void AWeapon::LoadAssetAsync_Implementation()
{
	// Anything that needs to be asynchronously loaded.
	// FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
}