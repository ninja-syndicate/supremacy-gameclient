// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CrowdAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintGameplayTagLibrary.h"
#include "Core/Game/SupremacyGameState.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/NavMovementComponent.h"

#include "Weapons/Weapon.h"
#include "Weapons/WeaponizedInterface.h"
#include "Weapons/Components/WeaponAmmunitionComponent.h"

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
		UE_LOG(LogTemp, Error, TEXT("CrowdAIController: Fatal! UWarMachineFollowingComponent is invalid. AI will not work properly..."));
		return;
	}
}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get the game state.
	ASupremacyGameState* GameState = Cast<ASupremacyGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!IsValid(GameState)) 
	{
		UE_LOG(LogTemp, Error, TEXT("ACrowdAIController: Unsupported game state!"));
		return;
	}

	// In case OnPossess gets called before BeginPlay(), initialize if the pawn is valid.
	if (IsValid(GetPawn()))
	{
		Initialize();
	}

	// Query for the match state and start AI if the battle has already started. Otherwise wait for the match start.
	const bool bHasMatchStarted = GameState->HasMatchStarted();
	if (bHasMatchStarted)
	{
		StartAI();
	}
	else
	{
		GameState->OnMatchStarted.AddDynamic(this, &ACrowdAIController::StartAI);
	}
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(InPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("ACrowdAIController: Attempt to possess an invalid pawn!"));
		return;
	}

	// TODO: Refactor blueprint so it uses Get Controlled Pawn.
	PossessedPawn = InPawn;
	if (!PossessedPawn->Implements<UWeaponizedInterface>())
	{
		UE_LOG(LogTemp, Warning, TEXT("ACrowdAIController: Possessed pawn does not implement IWeaponizedInterface!"));
		return;
	}

	// Initialize if the actor has already begun play. Otherwise let BeginPlay event handle initializing.
	if (HasActorBegunPlay())
	{
		Initialize();
	}
}

void ACrowdAIController::OnUnPossess()
{
	Super::OnUnPossess();

	DisableScript();
	PossessedPawn = nullptr;
}

//~ Begin ICombatAgentInterface
AActor* ACrowdAIController::GetCurrentTarget_Implementation() const
{
	return CurrentTarget;
}

bool ACrowdAIController::CanSeeTarget_Implementation() const
{
	// @stub: this is currently implemented in blueprints.
	return true;
}
//~ End ICombatAgentInterface

void ACrowdAIController::Initialize_Implementation()
{
	if (!IsValid(PossessedPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("ACrowdAIController: A valid possessed pawn is needed to initialize."));
		return;
	}

	// Get the skeletal mesh component of the possessed pawn to get its eyes view point.
	UActorComponent* Comp = PossessedPawn->GetComponentByClass(USkeletalMeshComponent::StaticClass());
	USkeletalMeshComponent* MeshComp = Cast<USkeletalMeshComponent>(Comp);
	if (!IsValid(MeshComp))
	{
		UE_LOG(LogTemp, Warning, TEXT("ACrowdAIController: Failed to get the skeletal mesh component of the pawn!"));
		return;
	}
	PossessedPawnMesh = MeshComp;

	bIsInitialized = true;
}

void ACrowdAIController::StartAI_Implementation()
{
	EnableScript();
}

void ACrowdAIController::StopAI_Implementation()
{
	if (!IsValid(GetPawn())) return;

	// Disable the running script.
	DisableScript();

	if (GetPawn()->Implements<UWeaponizedInterface>())
	{
		// Get all the weapons.
		TArray<AWeapon*> Weapons;
		IWeaponizedInterface::Execute_GetWeapons(PossessedPawn, Weapons);

		for (AWeapon* Weapon : Weapons)
		{
			Weapon->Release();
		}
	}
	
	// Get the nav movement component if it has one and stop movement immediately.
	UActorComponent* Comp = GetPawn()->GetComponentByClass(UNavMovementComponent::StaticClass());
	UNavMovementComponent* MoveComp = Cast<UNavMovementComponent>(Comp);
	if (MoveComp)
	{
		MoveComp->StopMovementImmediately();
	}
	StopMovement();
}

void ACrowdAIController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
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
	GetWorldTimerManager().ClearTimer(ScriptTickTimer);
	bIsScriptEnabled = false;
}

bool ACrowdAIController::GetTargetWeaponInfos(TArray<FAIWeaponInfo>& OutWeaponInfos)
{
	// TODO: Implementation
	// Only provide weapon infos relevant.
	return false;
}

bool ACrowdAIController::GetWeaponInfos(TArray<FAIWeaponInfo>& OutWeaponInfos)
{
	if (!IsValid(PossessedPawn)) return false;

	// Get all the weapons.
	TArray<AWeapon*> Weapons;
	IWeaponizedInterface::Execute_GetWeapons(PossessedPawn, Weapons);

	for (const AWeapon* Weapon : Weapons)
	{
		if (!IsValid(Weapon)) continue;

		FGameplayTagContainer GameplayTagContainer;
		Weapon->GetOwnedGameplayTags(GameplayTagContainer);

		// Break gameplay tag container into individual tags.
		TArray<FGameplayTag> GameplayTags;
		UBlueprintGameplayTagLibrary::BreakGameplayTagContainer(GameplayTagContainer, GameplayTags);
	
		// Go through each tag this weapon has.
		TArray<FString> WeaponTags;
		for (const FGameplayTag& GameplayTag : GameplayTags)
		{
			WeaponTags.Add(GameplayTag.GetTagName().ToString());
		}

		UActorComponent* Comp = Weapon->GetComponentByClass(UWeaponAmmunitionComponent::StaticClass());
		UWeaponAmmunitionComponent* AmmoComp = Cast<UWeaponAmmunitionComponent>(Comp);

		int WeaponCurrentAmmo = 0, WeaponMaxAmmo = 0;
		if (AmmoComp)
		{
			// TODO: Consider giving infinite ammo boolean variable?
			// If infinite ammo, give really large ammo count.
			WeaponCurrentAmmo = AmmoComp->IsInfiniteAmmo() ? 9999 : AmmoComp->GetAmmo();
			WeaponMaxAmmo = AmmoComp->IsInfiniteAmmo() ? 9999 : Weapon->Struct.Max_Ammo;
		}

		// Set up AI weapon info to send to the script.
		FAIWeaponInfo WeaponInfo;
		WeaponInfo.Hash = Weapon->Struct.Hash;
		WeaponInfo.Model = Weapon->Struct.Model_Name;
		WeaponInfo.Damage = Weapon->Struct.Damage;
		WeaponInfo.DamageFalloff = Weapon->Struct.Damage_Falloff;
		WeaponInfo.DamageFalloffRate = Weapon->Struct.Damage_Falloff_Rate;
		WeaponInfo.RadialDamageRadius = Weapon->Struct.Damage_Radius;
		WeaponInfo.RadialDamageFalloff = Weapon->Struct.Damage_Radius_Falloff;
		WeaponInfo.DamageType = Weapon->Struct.Damage_Type;
		WeaponInfo.Spread = Weapon->Struct.Spread;
		WeaponInfo.RateOfFire = Weapon->Struct.Rate_Of_Fire;
		WeaponInfo.BurstRateOfFire = Weapon->Struct.Burst_Rate_Of_Fire;
		WeaponInfo.ProjectileSpeed = Weapon->Struct.Projectile_Speed;
		WeaponInfo.CurrentAmmo = WeaponCurrentAmmo;
		WeaponInfo.MaxAmmo = WeaponMaxAmmo;
		WeaponInfo.Tags = WeaponTags;
		WeaponInfo.Slot = Weapon->Struct.Socket_Index;

		OutWeaponInfos.Add(WeaponInfo);
	}
	return true;
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
	if (!bIsInitialized) return false;

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
	if (!bIsInitialized) return false;

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
	if (!PossessedPawn) return;

	if (bEnableCustomEyesViewPoint)
	{
		if (!PossessedPawnMesh) return;

		out_Location = PossessedPawnMesh->GetSocketLocation("AI_Eyes");
		out_Rotation = PossessedPawnMesh->GetSocketRotation("AI_Eyes");
		return;
	}

	FVector EyesLocation;
	FRotator EyesRotation;
	Super::GetActorEyesViewPoint(EyesLocation, EyesRotation);

	if (bEnableEyesViewPointOffset) 
	{
		EyesLocation = FVector(EyesLocation.X, EyesLocation.Y, EyesLocation.Z + eyesViewPointOffset);
	}

	out_Location = EyesLocation;
	if (bEnableEyesMatchRotation) 
	{
		// TODO: Store reference to avoid getting the object cost.
		FRotator PawnRotation = PossessedPawn->GetActorRotation();
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
	TMap<FString, FAIEnvironmentQueryResult> EnvQueryStatus,
	FAIWarMachineInfo CommandTargetWarMachineInfo)
{
	FAIBrainInput BrainInput;
	BrainInput.Self = WarMachineInfo;
	BrainInput.DeltaTime = DeltaTime;
	BrainInput.Perception = PerceptionInfo;
	BrainInput.Errors = Errors;
	BrainInput.EnvQueryStatus = EnvQueryStatus;
	BrainInput.CommandTarget = CommandTargetWarMachineInfo;

	return BrainInput;
}

FString ACrowdAIController::ToJson(const FAIBrainInput& BrainInput)
{
	FString JsonString;
	FPascalCaseJsonObjectConverter::UStructToJsonObjectString(BrainInput, JsonString);
	return JsonString;
}