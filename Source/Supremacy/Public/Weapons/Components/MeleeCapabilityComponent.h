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

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Melee Capability Component")
	bool TriggerMelee();
	virtual bool TriggerMelee_Implementation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleAmmoChanged(int CurrentAmmo);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Melee Capability Component")
	TObjectPtr<class UBoxComponent> MeleeBoxComp = nullptr;

	UPROPERTY(Category = "Melee Capability Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName MeleeBoxCompTagName = FName("MeleeBoxComp");

	UPROPERTY(Category = "Melee Capability Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bUseBoxComp = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Melee Capability Component")
	bool bSwitchToMeleePose = false;
};
