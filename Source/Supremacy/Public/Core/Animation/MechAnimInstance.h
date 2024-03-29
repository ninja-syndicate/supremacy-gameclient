// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MechAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UMechAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMechAnimInstance();

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void PreUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintThreadSafe = true), Category = "Thread Safe Functions")
	void UpdateLocomotion(float DeltaSeconds);
	virtual void UpdateLocomotion_Implementation(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintThreadSafe = true), Category = "Thread Safe Functions")
	void UpdateUpperBody(float DeltaSeconds);
	virtual void UpdateUpperBody_Implementation(float DeltaSeconds);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Mech")
	void HandleMechInitialized();
	virtual void HandleMechInitialized_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Mech")
	void HandleWeaponEquipped(class AWeapon* Weapon);
	virtual void HandleWeaponEquipped_Implementation(class AWeapon* Weapon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	double Speed = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	double Direction = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator UpperBodyRot = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float UpperBodyTurnRate = 0.0f;

	/** Whether to use a custom upper body turn rate. If turned off, it will use character movement component's yaw turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	bool bCustomUpperBodyTurnRate = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInstance")
	TObjectPtr<class AMech> MechOwner = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimInstance")
	bool bIsInitialized = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Animation")
	float LocomotionAnimPlayRate = 1.0f;
	
private:
	/** 
	 * Accessed variables in the pre-event graph (game thread, before event-graph and NativeUpdateAnimation).
	 * To be used in the NativeThreadSafeUpdateAnimations().
	 */
	FVector PreVelocity = FVector::ZeroVector;
	FRotator PreRotation = FRotator::ZeroRotator;
	FRotator PreLookRotation = FRotator::ZeroRotator;
};
