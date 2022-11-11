// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/WarMachineStruct.h"
#include "Weapons/WeaponizedInterface.h"
#include "Mech.generated.h"

UCLASS()
class SUPREMACY_API AMech final : public ACharacter, public IWeaponizedInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMech();

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
	virtual class AWeapon* GetWeaponBySlot_Implementation(int SlotIndex) override;
	virtual void GetWeapons_Implementation(TArray<class AWeapon*>& OutWeapons) override;

	UPROPERTY(Category = "Weapon", Replicated, BlueprintReadWrite)
	TArray<class AWeapon*> Weapons;

protected:
	UFUNCTION()
	virtual void OnRep_SetWarMachineStruct();
};
