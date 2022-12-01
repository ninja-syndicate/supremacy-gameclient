// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UWeaponAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponAimComponent();

public:
	/** Returns currently aimed location via crosshair. */
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	FVector GetAimLocation() const;

	/** Returns the weapon barrel transform. */
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	FTransform GetBarrelTransform() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	FVector GetPlayerAimTargetTransform();
	FVector Trace(const FVector& CameraLocation, const FRotator& CameraRotation, const FVector& WeaponLocation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class AWeapon> Weapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> WeaponBarrelStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APawn> OwnerPawn = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector AimLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTransform BarrelTransform;

private:
	// @todo - move this to weapon or use damage_falloff if applicable.
	/**
	  * The distance of the trace performed when aiming.
	  * This focal distance will depend on the scale of the world. 
	  * 
	  * Do not make this value arbitrarily large as aiming will be very-off when aiming at empty space.
	  * If aiming accurately at really far distance is required, this focal distance value should be based on that specific weapon.
	  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float TraceDistance = 30000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float FocalDistance = 16384.0f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bIsInitialized = false;
};
