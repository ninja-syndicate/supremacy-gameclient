// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "Core/Game/SupremacyTypes.h"
#include "FlamethrowerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API AFlamethrowerWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	virtual void HitScan();

	UFUNCTION(Category="Weapon|Flamethrower", BlueprintCallable, BlueprintNativeEvent)
	void ApplyBurnDecal(const FHitResult& HitResult);
	virtual void ApplyBurnDecal_Implementation(const FHitResult& HitResult);

	UFUNCTION(Category = "Weapon|Flamethrower", BlueprintCallable, BlueprintNativeEvent)
	void ApplyBurning(const FHitResult& HitResult);
	virtual void ApplyBurning_Implementation(const FHitResult& HitResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BarrelSocketName = FName("Barrel");

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	/** @todo - Maybe make this global somewhere? */
	UPROPERTY(Category = "Weapon|Flamethrower", EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EPhysicalSurface>> NonflammableSurfaceTypes = {SurfaceType_Sand, SurfaceType_Energy};

	UPROPERTY(Category = "Weapon|Flamethrower", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> BurnDecalMat;

	UPROPERTY(Category = "Weapon|Flamethrower", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraComponent> BurningNiagaraComp;
};
