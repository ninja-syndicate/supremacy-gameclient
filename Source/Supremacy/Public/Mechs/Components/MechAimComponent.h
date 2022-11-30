// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ActorComponent.h"
#include "MechAimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UMechAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMechAimComponent();

public:
	UFUNCTION(BlueprintCallable)
	FVector GetAimLocation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	FVector GetTargetLocation();

	UFUNCTION(BlueprintCallable)
	FVector GetBaseAimLocation();

	UFUNCTION(BlueprintCallable)
	FVector GetPlayerAimLocation();

	UFUNCTION(BlueprintCallable)
	void GetCameraViewpoint(FVector& OutCameraLocation, FRotator& OutCameraRotation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleMechInitialized();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bIsInitialized = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class AMech> OwnerMech = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector CurrentAimLocation = FVector::ZeroVector;

private:
	/** Enables spring oscillation-based aiming. So it oscillates after reaching the target aim location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bEnableSpringAimInterpolation = true;

	// NOTE: This is enabled for now as we don't have any other options yet.
	/** Uses a trace to determine the aim location. Not recommended as the aim location can be very-off. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bEnableTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, EditCondition = "bEnableTrace"))
	float TraceDistance = 10000000.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVectorSpringState VectorSpringState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, EditCondition = "bEnableSpringAimInterpolation"))
	float SpringStiffness = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, EditCondition = "bEnableSpringAimInterpolation"))
	float SpringCriticalDampeningFactor = 0.2f;
};
