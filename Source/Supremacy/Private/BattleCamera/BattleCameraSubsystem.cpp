// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCamera/BattleCameraSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UBattleCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBattleCameraSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<AActor*> UBattleCameraSubsystem::GetBattleCameraTargets()
{
	return BattleCameraTargets;
}

void UBattleCameraSubsystem::RegisterTarget(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: Invalid actor cannot be registered."));
		return;
	}
	const FString Name = UKismetSystemLibrary::GetDisplayName(Actor);
	if (BattleCameraTargets.Contains(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: %s is already registered in the battle camera target list."), *Name);
		return;
	}
	if (bEnableDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: Actor %s registered."), *Name);
	}
	BattleCameraTargets.Add(Actor);
}

void UBattleCameraSubsystem::UnregisterTarget(AActor* Actor)
{
	if (!Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: The actor to unregister is nullptr."));
		return;
	}
	const FString Name = UKismetSystemLibrary::GetDisplayName(Actor);
	if (!BattleCameraTargets.Contains(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: %s is not registered in the battle camera target list."), *Name);
		return;
	}
	if (bEnableDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleCameraSubsystem: Actor %s unregistered."), *Name);
	}
	BattleCameraTargets.Remove(Actor);
}