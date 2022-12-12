// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

#include "Net/UnrealNetwork.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetGuidLibrary.h"
#include "BlueprintGameplayTagLibrary.h"
#include "Materials/MaterialInterface.h"

#include "Core/Game/SupremacyGameInstance.h"
#include "Core/Gameplay/GameplayTags.h"
#include "Core/Gameplay/GameplayTagFunctionLibrary.h"
#include "StaticData/StaticData.h"

// Sets default values
AWeapon::AWeapon() : Super()
{
 	// Some weapons may need Tick() so enable actor tick.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize replication settings.
	bReplicates = true;
	bAlwaysRelevant = true;

	// Set up root component.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Add the weapon gameplay tag.
	GameplayTagContainer.AddTag(TAG_Weapon);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	// @todo - port some functions and static mesh set up in weapons.
	// For barrel, just accept static mesh.
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
	// Append the init gameplay tags into the main gameplay tag container.
	UBlueprintGameplayTagLibrary::AppendGameplayTagContainers(
		GameplayTagContainer, UGameplayTagFunctionLibrary::GetAllTags(InitGameplayTagContainer));

	// If the weapon hash is not set, generate one for it.
	if (Struct.Hash.IsEmpty())
		GenerateHash();

	// Load the weapon skin asynchronously.
	LoadAssetAsync();

	// Nothing to do from now if instigator is not set.
	if (!GetInstigator()) return;

	// Get the children comps to ignore when moving (This may not be required?).
	TArray<USceneComponent*> ChildrenComps;
	RootComponent->GetChildrenComponents(true, ChildrenComps);

	for (USceneComponent* Comp : ChildrenComps)
	{
		UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(Comp);
		if (!PrimitiveComp) return;

		PrimitiveComp->IgnoreActorWhenMoving(this, true);
		PrimitiveComp->IgnoreActorWhenMoving(GetInstigator(), true);
	}

	// TODO: This should ideally be moved to subclasses.
	// TODO: Figure out a way to check all assets loaded and then dispatch.
	bIsInitialized = true;
	OnWeaponInitialized.Broadcast(this);

	if (GetInstigator()->Implements<UWeaponizedInterface>())
	{
		IWeaponizedInterface::Execute_PostWeaponInit(GetInstigator(), this);
	}
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

void AWeapon::GenerateHash()
{
	FGuid Guid = FGuid::NewGuid();

	Struct.Hash = Guid.ToString();
}

void AWeapon::LoadAssetAsync_Implementation()
{
	// Use the default skin if the skin id is empty.
	if (Struct.Skin_ID.IsEmpty()) return;

	// Anything that needs to be asynchronously loaded.
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	// Parse the model ID and skin ID into GUID.
	bool bModelIDParseSuccess = false, bSkinIDParseSuccess = false;
	FGuid ModelGuidID, SkinGuidID;
	UKismetGuidLibrary::Parse_StringToGuid(Struct.Model_ID, ModelGuidID, bModelIDParseSuccess);
	UKismetGuidLibrary::Parse_StringToGuid(Struct.Skin_ID, SkinGuidID, bSkinIDParseSuccess);

	// Get the game instance.
	USupremacyGameInstance* GameInstance = Cast<USupremacyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance)
	{
		UE_LOG(LogWeapon, Error, TEXT("AWeapon: Failed to retrieve the supremacy game instance!"));
		return;
	}
	if (!GameInstance->GetStaticData())
	{
		UE_LOG(LogWeapon, Error, TEXT("AWeapon: Invalid static data."));
		return;
	}

	// Get the skin for this weapon model.
	const TMap<FString, TSoftObjectPtr<UMaterial>>& WeaponMaterials = 
		GameInstance->GetStaticData()->MaterialsForWeapon(ModelGuidID, SkinGuidID);
	for (const auto& Pair : WeaponMaterials)
	{
		if (Pair.Value.IsNull()) continue;
	
		StreamableHandle.Add(Pair.Key, Streamable.RequestAsyncLoad(
			Pair.Value.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &AWeapon::LoadAssetDeferred)
		));
	}
}

void AWeapon::LoadAssetDeferred()
{
	for (const auto& WeaponStream : StreamableHandle)
	{
		if (!WeaponStream.Value.IsValid()) return;
		if (!WeaponStream.Value->HasLoadCompleted()) return;

		UMaterialInterface* Material = Cast<UMaterialInterface>(WeaponStream.Value->GetLoadedAsset());
		if (!Material) return;

		TArray<UStaticMeshComponent*> StaticComps;
		GetComponents<UStaticMeshComponent>(StaticComps, true);

		for (UActorComponent* Comp : StaticComps)
		{
			UStaticMeshComponent* StaticComp = Cast<UStaticMeshComponent>(Comp);
			if (!StaticComp) continue;

			if (StreamableHandle.Num() == 1)
				StaticComp->SetMaterial(0, Material);
			else
				StaticComp->SetMaterialByName(FName(WeaponStream.Key), Material);
		}
	}
}