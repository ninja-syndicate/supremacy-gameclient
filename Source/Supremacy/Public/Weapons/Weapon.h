// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "Types/WeaponStruct.h"
#include "Weapon.generated.h"

UCLASS()
class SUPREMACY_API AWeapon : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	FWeaponStruct Struct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	FVector TargetLocation;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Trigger();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Release();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags", Replicated)
    FGameplayTagContainer GameplayTagContainer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer; }
};
