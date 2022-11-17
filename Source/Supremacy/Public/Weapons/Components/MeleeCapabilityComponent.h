// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeCapabilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UMeleeCapabilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeCapabilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleNoAmmo();

private:
	UPROPERTY(Category = "Melee Capability Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName MeleeBoxCompTagName = FName("MeleeBoxComp");

	UPROPERTY(Category = "Melee Capability Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bUseBoxComp = true;

	UPROPERTY(Category = "Melee Capability Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bSwitchToMeleePose = false;
};
