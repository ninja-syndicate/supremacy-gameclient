// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_AIPerception.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UBPFL_AIPerception : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// https://github.com/EpicGames/UnrealEngine/pull/8649
	UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext = "WorldContextObject"))
	static void ReportTouchEvent(UObject* WorldContextObject, AActor* TouchReceiver, AActor* OtherActor, FVector Location);
};
