// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/AbilityID.h"
#include "Types/WarMachineStruct.h"
#include "UserAction/UserActionManager.h"
#include "Weapons/WeaponizedInterface.h"
#include "Mech.generated.h"

UCLASS()
class SUPREMACY_API AMech : public ACharacter, public IWeaponizedInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMech();

	virtual void BeginPlay() override;

public:
	//~ Begin IWeaponizedInterface
	virtual class AWeapon* GetWeaponBySlot_Implementation(int SlotIndex) override;
	virtual void GetWeapons_Implementation(TArray<class AWeapon*>& OutWeapons) override;
	virtual float GetWeaponBaseScale_Implementation() const override;
	virtual void PostWeaponInit_Implementation(class AWeapon* Weapon) override;
	//~ End IWeaponizedInterface

public:
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_SetWarMachineStruct, meta=(ExposeOnSpawn="true"))
	FWarMachineStruct WarMachineStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	bool IsReinforcement;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Setup();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Animation")
	void PlayAnimationIntro();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Animation")
	void PlayAnimationOutro();

public:
	UFUNCTION(BlueprintPure)
	bool IsInitialized() const;

public:
	/** 
	 * Dispatched after the mech is fully initialized. 
	 * Do not make this replicated as the initialization state will depend on individual PC.
	 * This is currently dispatched in the blueprint after weapon spawning is done.
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitialized);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Mech")
	FOnInitialized OnInitialized;

	/** Dispatched when the mech equips a new weapon. Currently, this is not dispatched on weapon spawn. */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, class AWeapon*, Weapon);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Mech")
	FOnWeaponEquipped OnWeaponEquipped;

	//~ Begin Mech Abilities
	UFUNCTION(BlueprintCallable, Server, Reliable, Category="Mech Abilities")
	void UseMechAbility(const EAbilityID Ability);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMechAbilityUsed, EAbilityID, Ability);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Mech Abilities")
	FOnMechAbilityUsed OnMechAbilityUsed;
	
	UPROPERTY(BlueprintReadOnly, Category = "Mech Abilities")
	TMap<EAbilityID, float> AbilityUseTimes;

protected:
	void HandleWeaponEquipped(class AWeapon* Weapon);

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
	TArray<class AWeapon*> Weapons;
	
	/** The scale to use for the weapons equipped by the mech. Intended to be set from blueprints/subclasses. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float WeaponBaseScale = 1.0f;
	
protected:
	/** Whether the mech is fully initialized. Do not make this replicated as it will depend on individual PC. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInitialized = false;

protected:
	UFUNCTION(BlueprintCallable, Category = "Mech|Replication")
	virtual void OnRep_SetWarMachineStruct();
	
	UPROPERTY()
	UUserActionManager* UserActionManager;
	
};
