// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScriptAPIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UScriptAPIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScriptAPIComponent();

public:
	// Begin Script API
	UFUNCTION(Category = "Script API|Weapon")
	bool WeaponTrigger(int Slot, FVector Location);

	UFUNCTION(Category = "Script API|Weapon")
	bool WeaponRelease(int Slot);
	// End Script API

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	/** Enables the AI script. */
	UFUNCTION(Category = "Script API Component", BlueprintCallable, CallInEditor)
	void EnableScript();

	/** Disables the AI script. */
	UFUNCTION(Category = "Script API Component", BlueprintCallable, CallInEditor)
	void DisableScript();

protected:
	UPROPERTY(Category = "Script API Component", EditAnywhere, BlueprintReadWrite)
	bool bIsScriptEnabled = false;

	/** @todo - documentation */
	UPROPERTY(Category = "Script API Component", EditAnywhere, BlueprintReadWrite)
	int MaxCallPerTick = 100;

	UPROPERTY(Category = "Script API Component", EditAnywhere, BlueprintReadWrite)
	int MaxImmediateCallPerTick = 10;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
