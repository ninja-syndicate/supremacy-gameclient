// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "CrowdAIController.generated.h"

UENUM(BlueprintType)
enum EAvoidanceType
{
	Unused1		UMETA(DisplayName = "Unused1"),
	Unused2		UMETA(DisplayName = "Unused2"),
	Mech		UMETA(DisplayName = "Mech"),
	Dog			UMETA(DisplayName = "Dog")
};

/**
 * 
 */
UCLASS()
class SUPREMACY_API ACrowdAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACrowdAIController(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;

	// NOTE: These cooldown functions will be removed later.
	UFUNCTION(BlueprintCallable)
	virtual void SetCooldown(const FGameplayTag& ActionTag, float Cooldown);

	UFUNCTION(BlueprintNativeEvent)
	void OnCooldownEnd(const FGameplayTag ActionTag);
	void OnCooldownEnd_Implementation(const FGameplayTag ActionTag);

protected:
	/** Whether to enable crowd separation or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableSeparation;

	/** The weight applied to the separation of the agents. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	float SeparationWeight;

	/** The range to check for the collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	float CollisionQueryRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	float PathOptimizationRange;

	/** Slowdown the agent when it reaches close to the goal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableSlowdownAtGoal;

	/** Whether to optimise visibility. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableOptimizeVisibility;

	/** Whether to optimise topology. Recommended to be turned-off as it is buggy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnableOptimizeTopology;

	/** Whether to enable path offset. topology. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	bool bEnablePathOffset;

	/** For setting the avoidance type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detour Crowd AI")
	TEnumAsByte<EAvoidanceType> AvoidanceType;

	/** Whether to enable eyes view-point offset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Configuration")
	bool bEnableEyesViewPointOffset;

	/**
	 * Whether to enable custom eyes view-point offset.
	 * Requires pawn to have a skeletal mesh and its skeleton to have a AI_Eyes socket that's ideally attached in-between (centre) two eyes.
	 *
	 * Note that this option takes precedence over bEnableEyesViewPointOffset and bEnableEyesMatchRotation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Configuration")
	bool bEnableCustomEyesViewPoint;

	/**
	 * Default eyes viewpoint offset added to the centre of the pawn.
	 * Used for AI traces.
	 *
	 * Note that this option is only relevant when bEnableEyesViewPointOffset is enabled and bEnableCustomEyesViewPoint is disabled.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Configuration")
	float eyesViewPointOffset;

	/**
	 * Whether to match the eyes rotation to the pawn's rotation.
	 * Usually this should be set to true unless you have enabled bEnableCustomEyesViewPoint and uses different rotation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Configuration")
	bool bEnableEyesMatchRotation;

	/** Reference to the current crowd following component. */
	UPROPERTY()
	class UCrowdFollowingComponent* CrowdFollowingComponent;
};
