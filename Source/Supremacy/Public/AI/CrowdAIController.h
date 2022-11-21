// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "Types/AI/AIBrainInput.h"
#include "Types/AI/AIWarMachineInfo.h"
#include "Types/AI/AIEnvironmentQueryResult.h"
#include "Types/AI/AIPerceptionInfo.h"
#include "Types/AI/AIScriptLog.h"
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
	
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;

	// TEMP: Need to refactor.
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "WarMachineInfo, DeltaTime, PerceptionInfo, Errors, EnvQueryStatus"))
	FAIBrainInput GetBrainInput(
		FAIWarMachineInfo WarMachineInfo,
		float DeltaTime,
		FAIPerceptionInfo PerceptionInfo,
		TArray<FAIScriptLog> Errors,
		TMap<FString, FAIEnvironmentQueryResult> EnvQueryStatus);

	// NOTE: These cooldown functions will be removed later.
	UFUNCTION(BlueprintCallable)
	virtual void SetCooldown(const FGameplayTag& ActionTag, float Cooldown);

	UFUNCTION(BlueprintNativeEvent)
	void OnCooldownEnd(const FGameplayTag ActionTag);
	void OnCooldownEnd_Implementation(const FGameplayTag ActionTag);

public:
	//~ Begin Script API
	//UFUNCTION(Category = "Script API", BlueprintCallable)
	//bool SetFocalPointByHash(FString Hash);

	UFUNCTION(Category = "Script API", BlueprintCallable)
	void ClearFocalPoint();

	UFUNCTION(Category = "Script API", BlueprintCallable)
	bool WeaponTrigger(int Slot, FVector Location);

	UFUNCTION(Category = "Script API", BlueprintCallable)
	bool WeaponRelease(int Slot);
	//~ End Script API

protected:
	/** The current target actor set by the script. */
	UPROPERTY(Category = "Script AI Controller", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> CurrentTarget = nullptr;

protected:
	UFUNCTION(Category = "Script AI Controller", BlueprintCallable, BlueprintNativeEvent)
	void Initialize();
	virtual void Initialize_Implementation();

	UFUNCTION(Category = "Script AI Controller", BlueprintCallable, BlueprintNativeEvent)
	void StartAI();
	virtual void StartAI_Implementation();

	UFUNCTION(Category = "Script AI Controller", BlueprintCallable, BlueprintNativeEvent)
	void StopAI();
	virtual void StopAI_Implementation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInitialized = false;

	/** The possessed pawn of this controller. */
	UPROPERTY(Category = "Script AI Controller", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APawn> PossessedPawn = nullptr;

	/** The skeletal mesh of the possessed pawn if available. */
	UPROPERTY(Category = "Script AI Controller", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> PossessedPawnMesh = nullptr;

protected:
	// TODO: Separate for the target ideally.
	UFUNCTION(Category = "Script AI Controller", BlueprintCallable)
	virtual bool GetTargetWeaponInfos(TArray<FAIWeaponInfo>& OutWeaponInfos);

	UFUNCTION(Category = "Script AI Controller", BlueprintCallable)
	virtual bool GetWeaponInfos(TArray<FAIWeaponInfo>& OutWeaponInfos);

	UPROPERTY(Category = "Script AI Controller", EditAnywhere, BlueprintReadWrite)
	FTimerHandle ScriptTickTimer;

private:
	//~ Begin Script AI Debugging functions.
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Script AI Debugging")
	void EnableScript();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Script AI Debugging")
	void DisableScript();
	//~ End Script AI Debugging functions.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script AI Debugging", meta = (AllowPrivateAccess = true))
	bool bIsScriptEnabled = false;

protected:
	UFUNCTION(BlueprintCallable, Category = "AI Utils")
	FString ToJson(const FAIBrainInput& BrainInput);

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

	/** Reference to the current mech following component. */
	UPROPERTY()
	class UWarMachineFollowingComponent* MechFollowingComponent;
};
