// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/WarMachineStruct.h"
#include "Mech.generated.h"

UCLASS()
class SUPREMACY_API AMech final : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMech();

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_SetWarMachineStruct, meta=(ExposeOnSpawn="true"))
	FWarMachineStruct WarMachineStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	bool IsReinforcement;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Setup();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Animation")
	void PlayAnimationIntro();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Animation")
	void PlayAnimationOutro();
	
protected:
	UFUNCTION()
	virtual void OnRep_SetWarMachineStruct();
};
