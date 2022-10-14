// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AvoidanceSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FAvoidanceAgentInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity = FVector::ZeroVector;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AgentRadius = 0.0f;
}

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
	bool RegisterAgent(APawn* Agent);

	UFUNCTION(BlueprintCallable)
	bool UnregisterAgent(APawn* Agent);

	UFUNCTION(BlueprintCallable)
	const TArray<FAvoidanceAgentInfo>& GetAgentInfos();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<FAvoidanceAgentInfo> AgentInfos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<APawn>> Agents;
};
