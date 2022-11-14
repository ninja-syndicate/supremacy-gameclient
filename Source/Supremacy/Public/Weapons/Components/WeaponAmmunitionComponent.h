// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAmmunitionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UWeaponAmmunitionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponAmmunitionComponent();

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Category = "Weapon Ammunition Component", BlueprintPure)
	int GetAmmo() const;

	UFUNCTION(Category = "Weapon Ammunition Component", BlueprintPure)
	bool HasAmmo() const;

	UFUNCTION(Category = "Weapon Ammunition Component", BlueprintPure)
	bool IsInfiniteAmmo() const;

	UFUNCTION(Category = "Weapon Ammunition Component", BlueprintCallable)
	void ReduceAmmo();

	UFUNCTION(Category = "Weapon Ammunition Component", BlueprintCallable)
	void RefillAmmo();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int, CurrentAmmo);
	UPROPERTY(BlueprintAssignable, Category = "Weapon Ammunition Component")
	FOnAmmoChanged OnAmmoChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Category = "Weapon Ammunition Component", Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int CurrentAmmo = 0;

	UPROPERTY(Category = "Weapon Ammunition Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int MaxAmmo = 0;

	UPROPERTY(Category = "Weapon Ammunition Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bEnableInfiniteAmmo = false;
};
