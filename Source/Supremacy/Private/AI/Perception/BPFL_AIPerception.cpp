// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Perception/BPFL_AIPerception.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Touch.h"

// https://github.com/EpicGames/UnrealEngine/pull/8649
void UBPFL_AIPerception::ReportTouchEvent(UObject* WorldContextObject, AActor* TouchReceiver, AActor* OtherActor, FVector Location)
{
	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(WorldContextObject);
	if (PerceptionSystem)
	{
		FAITouchEvent Event(TouchReceiver, OtherActor, Location);
		PerceptionSystem->OnEvent(Event);
	}
}