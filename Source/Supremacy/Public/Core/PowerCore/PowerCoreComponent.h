// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerCoreComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUPREMACY_API UPowerCoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerCoreComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetWeaponSystemCurrentPower();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetShieldSystemCurrentPower();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetMovementSystemCurrentPower();
};
