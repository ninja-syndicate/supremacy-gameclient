// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CrowdAIController.h"

#include "Weapons/Weapon.h"
#include "Weapons/WeaponizedInterface.h"

#include "AI/WarMachineFollowingComponent.h"
#include "Parsers/PascalCaseJsonObjectConverter.h"

ACrowdAIController::ACrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWarMachineFollowingComponent>(TEXT("PathFollowingComponent")))
{
	bEnableEyesViewPointOffset = false;
	bEnableCustomEyesViewPoint = false;
	bEnableEyesMatchRotation = true;
	eyesViewPointOffset = 256;

	MechFollowingComponent = Cast<UWarMachineFollowingComponent>(GetPathFollowingComponent());
	if (!MechFollowingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: Fatal! UWarMachineFollowingComponent is invalid. AI will not work properly..."));
		return;
	}
}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	EnableScript();
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = InPawn;
}

void ACrowdAIController::OnUnPossess()
{
	Super::OnUnPossess();

	PossessedPawn = nullptr;
	DisableScript();
}

void ACrowdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrowdAIController::EnableScript()
{
	bIsScriptEnabled = true;
}

void ACrowdAIController::DisableScript()
{
	bIsScriptEnabled = false;
}

//~Begin Script API
/*
bool ACrowdAIController::SetFocalPointByHash(FString Hash)
{
	// TODO:
	// SetFocus();
}
*/

void ACrowdAIController::ClearFocalPoint()
{
	ClearFocus(EAIFocusPriority::Gameplay);
}

bool ACrowdAIController::WeaponTrigger(int Slot, FVector Location)
{
	if (!IsValid(PossessedPawn)) return false;
	if (!PossessedPawn->Implements<UWeaponizedInterface>()) return false;

	AWeapon* Weapon = IWeaponizedInterface::Execute_GetWeaponBySlot(PossessedPawn, Slot);
	if (!IsValid(Weapon)) return false;

	// TODO: Support Location.
	if (Weapon->Struct.Is_Arced && IsValid(CurrentTarget))
	{
		// Set the target location to the current target's location for now.
		// TODO: Probably need constraint and possibly prediction.
		Weapon->TargetLocation = CurrentTarget->GetActorLocation();
	}
	Weapon->Trigger();
	return true;
}

bool ACrowdAIController::WeaponRelease(int Slot)
{
	if (!IsValid(PossessedPawn)) return false;
	if (!PossessedPawn->Implements<UWeaponizedInterface>()) return false;

	AWeapon* Weapon = IWeaponizedInterface::Execute_GetWeaponBySlot(PossessedPawn, Slot);
	if (!IsValid(Weapon)) return false;
	
	Weapon->Release();
	return true;
}
//~End Script API

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