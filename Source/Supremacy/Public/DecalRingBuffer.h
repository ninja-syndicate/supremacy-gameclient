// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/RingBuffer.h"
#include "PooledDecalActor.h"
#include "DecalRingBuffer.generated.h"

USTRUCT(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
struct FPooledDecalType {
	GENERATED_BODY()

	int CurrentIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Capacity = 0;

	TArray<APooledDecalActor*> Buffer;

	FPooledDecalType() {
		CurrentIndex = 0;
		Capacity = 0;
	}
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class SUPREMACY_API UDecalRingBuffer : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FPooledDecalType> DecalBuffers;

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ADecalActor* AllocateDecal(FString DecalType, float LifeTime, UMaterialInstanceDynamic* Material);
};
