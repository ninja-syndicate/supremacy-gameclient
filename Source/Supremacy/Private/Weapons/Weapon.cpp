// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

#include "Net/UnrealNetwork.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetGuidLibrary.h"
#include "BlueprintGameplayTagLibrary.h"

#include "Core/Game/SupremacyGameInstance.h"
#include "Core/Gameplay/GameplayTagFunctionLibrary.h"
#include "StaticData/StaticData.h"

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
	
		StreamableHandle = Streamable.RequestAsyncLoad(
			Pair.Value.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &AWeapon::LoadAssetDeferred)
		);
	}
}

void AWeapon::LoadAssetDeferred()
{
	if (!StreamableHandle.IsValid()) return;
	if (!StreamableHandle->HasLoadCompleted()) return;

	UMaterialInstance* Material = Cast<UMaterialInstance>(StreamableHandle->GetLoadedAsset());
	if (!Material) return;

	TArray<UStaticMeshComponent*> StaticComps;
	GetComponents<UStaticMeshComponent>(StaticComps, true);

	for (UActorComponent* Comp : StaticComps)
	{
		UStaticMeshComponent* StaticComp = Cast<UStaticMeshComponent>(Comp);
		if (!StaticComp) continue;

		StaticComp->SetMaterial(0, Material);
	}
}