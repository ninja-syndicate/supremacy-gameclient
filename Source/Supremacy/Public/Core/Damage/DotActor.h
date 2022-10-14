// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Damage/DotDamageParams.h"
#include "GameFramework/Actor.h"
#include "DotActor.generated.h"

UCLASS(Abstract)
class SUPREMACY_API ADotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADotActor();

	friend class UDamager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage();
	virtual void ApplyDamage_Implementation();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	bool DestroyCondition();
	virtual bool DestroyCondition_Implementation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<class UDamager> Damager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
	FDotDamageParams DotDamageParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int CurrentTickCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FTimerHandle DotTimerHandle;

};
