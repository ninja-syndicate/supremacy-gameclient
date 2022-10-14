// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SteeringBehaviorComponent.generated.h"

/**
 * Adds a steering behavior to the AI.
 * 
 * Intended to be attached to AAIController.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API USteeringBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USteeringBehaviorComponent();

	FVector Separation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OnPossessedPawnChanged();
	void Initialize(APawn* Pawn);

private:
	/** The possessed pawn of the owning AI controller. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APawn> PossessedPawn = nullptr;

	/** Reference to the owner AI controller. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class AAIController> OwnerController = nullptr;

	/** Reference to the avoidance subsystem. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAvoidanceSubsystem> AvoidanceSubsystem = nullptr;

	/** 
	 * The separation query range. This is the distance at which the agent starts to consider separation.
	 * The recommended value is AgentRadius * 12.0f.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SeparationQueryRange = 0.0f;

	/** The currently detected agent radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AgentRadius = 0.0f;

};
