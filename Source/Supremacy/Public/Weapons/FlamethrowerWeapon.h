// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraDataInterfaceExport.h"
#include "Weapons/Weapon.h"
#include "Core/Game/SupremacyTypes.h"
#include "FlamethrowerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API AFlamethrowerWeapon : public AWeapon, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
	
public:
	AFlamethrowerWeapon();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

public:
	//~Begin INiagaraParticleCallbackHandler
	virtual void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffset) override;
	//~End INiagaraParticleCallbackHandler

public:
	virtual void Trigger_Implementation() override;
	virtual void Release_Implementation() override;

protected:
	virtual void HitScan();

	UFUNCTION(Category="Weapon|Flamethrower", BlueprintCallable, BlueprintNativeEvent)
	void ApplyBurnDecal(const FHitResult& HitResult);
	virtual void ApplyBurnDecal_Implementation(const FHitResult& HitResult);

	UFUNCTION(Category = "Weapon|Flamethrower", BlueprintCallable, BlueprintNativeEvent)
	void ApplyBurning(const FHitResult& HitResult);
	virtual void ApplyBurning_Implementation(const FHitResult& HitResult);

protected:
	// @todo - Some clean-up later
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BarrelSocketName = FName("Barrel");

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp = nullptr;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UShapeComponent> MeleeBoxComp = nullptr;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDamager> Damager = nullptr;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraComponent> FlameStreamNiagaraComp = nullptr;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraComponent> BurningNiagaraComp = nullptr;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere)
	TObjectPtr<UMaterialInterface> BurnDecalMat = nullptr;

protected:
	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere)
	TArray<TEnumAsByte<EPhysicalSurface>> NonflammableSurfaceTypes;

private:
	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere)
	float CurrentChargeTime = 0.0f;

	UPROPERTY(Category = "Weapon|Flamethrower", VisibleAnywhere)
	float ScanTickInterval = 0.0f;
};
