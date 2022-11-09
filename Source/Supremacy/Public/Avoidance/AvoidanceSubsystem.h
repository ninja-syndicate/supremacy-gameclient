// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AvoidanceFlags.h"
#include "AvoidanceSubsystem.generated.h"

/**
 * Current agent information.
 */
USTRUCT(BlueprintType)
struct FAvoidanceAgentInfo 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;
};


USTRUCT(BlueprintType)
struct FAgentAvoidanceSettings 
{
	GENERATED_BODY()
public:
	/** The agent radius used for the avoidance. Doesn't need to be matched exactly with the actual agent radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float AgentRadius = 0.0f;

	/** The distance at which the separation starts to take place. Recommended value is `AgentRadius` * 13.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float SeparationQueryRange = 0.0f;

	/** The distance at which the steering starts to take place. Recommended value is `AgentRadius` * 30.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float SteeringQueryRange = 0.0f;

	/** Maximum acceleration speed for the agent. If the agent does not use acceleration, you can provide the maximum speed of the agent here. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance Agent Settings")
	float MaxAccelerationSpeed = 0.0f;
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
	bool Steering(APawn* Agent, FVector& OutSteeringForce);
	bool ObstacleAvoidance(APawn* Agent, FVector& OutObstacleAvoidanceForce);

private:
	FVector GetSeparationForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings);
	FVector GetSteeringForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings);
	FVector GetObstacleAvoidanceForce(APawn* Agent, const FAgentAvoidanceSettings& AvoidanceSettings);

private:
	UPROPERTY(Category = "Avoidance Subsystem", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<APawn*, FAgentAvoidanceSettings> Agents;

	UPROPERTY(Category = "Avoidance Subsystem", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bAutoRegisterPlayerPawn = true;

	UPROPERTY(Category = "Avoidance Subsystem", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float PlayerRVOAvoidanceWeight = 0.0f;

	UPROPERTY(Category = "Avoidance Subsystem", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bUseRVOAvoidance = true;
};
