// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "Components/ActorComponent.h"
#include "Damageable.generated.h"

// @todo - need to reparent existing damageable to c++ damageable.
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UDamageable : public UActorComponent, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageable();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	//~Begin IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer; }
	//~End IGameplayTagAssetInterface

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Damageable|Gameplay Tags")
	FGameplayTagContainer GameplayTagContainer;
};
