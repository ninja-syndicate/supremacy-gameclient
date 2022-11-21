// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "Types/WeaponStruct.h"
#include "Weapon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All);

UCLASS()
class SUPREMACY_API AWeapon : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, meta=(ExposeOnSpawn="true"))
	FWeaponStruct Struct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	FVector TargetLocation;

public:
	UFUNCTION(Category = "Weapon", BlueprintPure)
	bool IsTriggered() const;

	UFUNCTION(Category = "Weapon", BlueprintNativeEvent, BlueprintCallable)
	void Trigger();
	virtual void Trigger_Implementation();

	UFUNCTION(Category = "Weapon", BlueprintNativeEvent, BlueprintCallable)
	void Release();
	virtual void Release_Implementation();

	UFUNCTION(Category = "Weapon", BlueprintPure)
	bool CanFriendlyFire() const;

	UFUNCTION(Category = "Weapon", BlueprintCallable)
	void SetFriendlyFire(bool Enable);

public:
	/** Note that it will only dispatch the event when the `bIsTriggered` state changes rather than on every Trigger/Release. */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTriggerStateChanged, bool, bIsTriggered);
	UPROPERTY(Category = "Weapon", BlueprintAssignable)
	FOnTriggerStateChanged OnTriggerStateChanged;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadWrite)
	bool bIsTriggered = false;

	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadWrite)
	bool bEnableFriendlyFire = false;

protected:
	/** Gameplay tags passed on spawn and then appended to the main gameplay tag container in BeginPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, meta = (ExposeOnSpawn = true), Category = "Weapon|Gameplay Tags")
	FGameplayTagContainer InitGameplayTagContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags", Replicated)
    FGameplayTagContainer GameplayTagContainer;

protected:
	/** Indicates whether this weapon is properly initialized so it can be used. */
	UPROPERTY(Category = "Weapon", VisibleAnywhere, BlueprintReadWrite)
	bool bIsInitialized = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//~Begin IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer; }
	//~End IGameplayTagAssetInterface
};
