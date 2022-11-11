// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CrowdAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BlueprintGameplayTagLibrary.h"
#include "GameFramework/GameStateBase.h"

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
		UE_LOG(LogTemp, Warning, TEXT("CrowdAIController: Fatal! UWarMachineFollowingComponent is invalid. AI will not work properly..."));
		return;
	}
}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	const AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	if (!IsValid(GameState)) 
	{
		UE_LOG(LogTemp, Error, TEXT("ACrowdAIController: Unable to retrieve the game state!"));
		return;
	}

	const bool bHasMatchStarted = GameState->HasMatchStarted();
	if (bHasMatchStarted)
	{
		// Initialize();
	}
	else
	{
		// Bind event to the game state and intialize.

	}
	EnableScript();
	bIsInitialized = true;
}

void ACrowdAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = InPawn;
	if (!PossessedPawn->Implements<UWeaponizedInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("ACrowdAIController: Possessed pawn does not implement IWeaponizedInterface!"));
		return;
	}
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
	if (!IsValid(PossessedPawn)) return false;

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