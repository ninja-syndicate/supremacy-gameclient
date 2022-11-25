// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponizedInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponizedInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPREMACY_API IWeaponizedInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weaponized")
	class AWeapon* GetWeaponBySlot(int SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weaponized")
	void GetWeapons(TArray<class AWeapon*>& OutWeapons);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weaponized")
	float GetWeaponBaseScale() const;
	virtual float GetWeaponBaseScale_Implementation() const;

	/** Called the first time the weapon finishes initialization. This should be called after BeginPlay(). */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weaponized|Replication")
	void PostWeaponInit(class AWeapon* Weapon);
};
