// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CrowdAIController.h"

#include "AI/WarMachineFollowingComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Parsers/PascalCaseJsonObjectConverter.h"

ACrowdAIController::ACrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWarMachineFollowingComponent>(TEXT("PathFollowingComponent")))
{
	bEnableSeparation = true;
	bEnableEyesViewPointOffset = false;
	bEnableCustomEyesViewPoint = false;
	bEnableEyesMatchRotation = true;
	eyesViewPointOffset = 256;
	SeparationWeight = 2;
	CollisionQueryRange = 8400; // Approximately 16 * AgentRadius.
	PathOptimizationRange = 10000;
}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AvoidanceType == EAvoidanceType::Unused1 || AvoidanceType == EAvoidanceType::Unused2)
	{
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: Unused avoidance type is being used."));
	}

	CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (!CrowdFollowingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: CrowdFollowingComponent is invalid. AI will not work properly..."));
	}
	else
	{
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(static_cast<ECrowdAvoidanceQuality::Type>(AvoidanceType.GetValue()));
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
		CrowdFollowingComponent->SetCrowdPathOptimizationRange(PathOptimizationRange);
		// CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Type::High);
		CrowdFollowingComponent->SetCrowdSeparation(bEnableSeparation);
		CrowdFollowingComponent->SetCrowdSeparationWeight(SeparationWeight);
		CrowdFollowingComponent->SetCrowdSlowdownAtGoal(bEnableSlowdownAtGoal);
		CrowdFollowingComponent->SetCrowdOptimizeVisibility(bEnableOptimizeVisibility);
		CrowdFollowingComponent->SetCrowdOptimizeTopology(bEnableOptimizeTopology);
		CrowdFollowingComponent->SetCrowdPathOffset(bEnablePathOffset);
	}
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACrowdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * This function needs to be overriden to provide correct eyes location and rotation if AIPerception is being used.
 */
void ACrowdAIController::GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const
{
	if (bEnableCustomEyesViewPoint)
	{
		// TODO: Store reference to avoid getting the object cost.
		const APawn* ControlledPawn = GetPawn();
		if (!IsValid(ControlledPawn)) return;
		
		const USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(ControlledPawn->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (!IsValid(Mesh)) return;

		out_Location = Mesh->GetSocketLocation("AI_Eyes");
		out_Rotation = Mesh->GetSocketRotation("AI_Eyes");
		return;
	}

	FVector EyesLocation;
	FRotator EyesRotation;
	Super::GetActorEyesViewPoint(EyesLocation, EyesRotation);

	if (bEnableEyesViewPointOffset) {
		EyesLocation = FVector(EyesLocation.X, EyesLocation.Y, EyesLocation.Z + eyesViewPointOffset);
	}
	out_Location = EyesLocation;

	if (bEnableEyesMatchRotation) {
		// TODO: Store reference to avoid getting the object cost.
		const APawn* ControlledPawn = GetPawn();
		if (!IsValid(ControlledPawn)) return;

		FRotator PawnRotation = ControlledPawn->GetActorRotation();
		EyesRotation = PawnRotation;
	}
	out_Rotation = EyesRotation;
}

/**
 * These functions are for setting the cooldown for now. These will be eventually replaced by GAS.
 */
void ACrowdAIController::SetCooldown(const FGameplayTag& ActionTag, float Cooldown)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ACrowdAIController::OnCooldownEnd, ActionTag);

	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Cooldown, false);
}

void ACrowdAIController::OnCooldownEnd_Implementation(const FGameplayTag ActionTag)
{
}

FAIBrainInput ACrowdAIController::GetBrainInput(
	FAIWarMachineInfo WarMachineInfo,
	float DeltaTime,
	FAIPerceptionInfo PerceptionInfo,
	TArray<FAIScriptLog> Errors,
	TMap<FString, FAIEnvironmentQueryResult> EnvQueryStatus)
{
	FAIBrainInput BrainInput;
	BrainInput.Self = WarMachineInfo;
	BrainInput.DeltaTime = DeltaTime;
	BrainInput.Perception = PerceptionInfo;
	BrainInput.Errors = Errors;
	BrainInput.EnvQueryStatus = EnvQueryStatus;

	return BrainInput;
}

FString ACrowdAIController::ToJson(const FAIBrainInput& BrainInput)
{
	FString JsonString;
	FPascalCaseJsonObjectConverter::UStructToJsonObjectString(BrainInput, JsonString);
	return JsonString;
}