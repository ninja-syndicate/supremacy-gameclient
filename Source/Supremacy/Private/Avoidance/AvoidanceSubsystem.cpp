// Fill out your copyright notice in the Description page of Project Settings.


#include "Avoidance/AvoidanceSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UAvoidanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAvoidanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAvoidanceSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

bool UAvoidanceSubsystem::RegisterAgent(APawn* Agent)
{
	if (Agents.Contains(Agent)) return false;
	
	Agents.Add(Agent);
	return true;
}

bool UAvoidanceSubsystem::UnregisterAgent(APawn* Agent)
{
	const int32 NumRemoved = Agents.Remove(Agent);
	return NumRemoved > 0;
}

const TArray<FAvoidanceAgentInfo>& UAvoidanceSubsystem::GetAgentInfos()
{
	return AgentInfos;
}