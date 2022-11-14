// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MechHackComponent.generated.h"

USTRUCT()
struct FWeaponState
{
	GENERATED_BODY()
public:
	int Slot;
	bool bIsTriggered;
	bool bCanFriendlyFire;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UMechHackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMechHackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(Category = "Mech Hack Component", BlueprintCallable)
	void Hack();

	UFUNCTION(Category = "Mech Hack Component", BlueprintCallable)
	void Unhack();

protected:
	UFUNCTION(Category = "Mech Hack Component", BlueprintNativeEvent)
	void InitHackDuration();
	virtual void InitHackDuration_Implementation();

	UFUNCTION(Category = "Mech Hack Component", BlueprintNativeEvent)
	void AddHackEffect();
	virtual void AddHackEffect_Implementation();

private:
	void SaveWeaponStates();

private:
	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APawn> OwnerPawn = nullptr;

	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> OwnerMeshComp = nullptr;

	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* HackNiagaraComponent = nullptr;

	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsInitialized = false;

	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsHacked = false;

	UPROPERTY(Category = "Mech Hack Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UNiagaraSystem* HackNiagaraSystem = nullptr;

	UPROPERTY(Category = "Mech Hack Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float HackDuration = 0.0f;

	UPROPERTY(Category = "Mech Hack Component", VisibleAnywhere)
	TArray<FWeaponState> WeaponStates;
};
