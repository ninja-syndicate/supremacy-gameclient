// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BattleCameraSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UBattleCameraSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Battle Camera Subsystem")
	TArray<AActor*> GetBattleCameraTargets();

	UFUNCTION(BlueprintCallable, Category = "Battle Camera Subsystem")
	void RegisterTarget(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Battle Camera Subsystem")
	void UnregisterTarget(AActor* Actor);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle Camera Subsystem", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> BattleCameraTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Camera Subsystem", meta = (AllowPrivateAccess = "true"))
	bool bEnableDebug;
};
