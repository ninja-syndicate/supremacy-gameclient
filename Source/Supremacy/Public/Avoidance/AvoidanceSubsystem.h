// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AvoidanceSubsystem.generated.h"

/**
 * Current agent information.
 */
USTRUCT(BlueprintType)
struct FAvoidanceAgentInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;
};


USTRUCT(BlueprintType)
struct FAgentAvoidanceSettings {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float AgentRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float SeparationQueryRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float MaxSeparationForce = 0.0f;
};

/**
 * 
 */
UCLASS()
class SUPREMACY_API UAvoidanceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable)
	bool RegisterAgent(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings);

	UFUNCTION(BlueprintCallable)
	bool UnregisterAgent(APawn* Agent);

	bool Separation(APawn* Agent, FVector& OutSeparationForce);

	// Uses the pawn's cylinder to calculate the agent radius and height.
	bool CalcAgentBounds(APawn* Agent, float& OutCylinderRadius, float& OutCylinderHeight);

private:
	FVector GetSeparationForce(APawn* Pawn, const FAgentAvoidanceSettings& AvoidanceSettings);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<FAvoidanceAgentInfo> AgentInfos;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<APawn*, FAgentAvoidanceSettings> Agents;
};
