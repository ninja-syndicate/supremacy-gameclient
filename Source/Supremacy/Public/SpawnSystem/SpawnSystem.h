// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnSystem.generated.h"

class ASpawnTestActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API USpawnSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/**
	 * Returns a closest actor with the given tag from the specified location.
	 * 
	 * @param Location The origin location to search for the closest actor.
	 * @param Tag The tag name used to find actors.
	 * @param OutSuccess Indicates whether such an actor is found.
	 * @return Reference to such an actor.
	 */
	UFUNCTION(BlueprintCallable, Category="Spawn System")
	AActor* GetClosestActorWithTag(FVector Location, FName Tag, bool& OutSuccess);

	/** Occupies a given location by placing an invisible spawn test actor of the given radius. */
	UFUNCTION(BlueprintCallable)
	void OccupyLocation(const FVector& Location, float Radius);

	/** Frees a given location occupied by the spawn test actor. */
	UFUNCTION(BlueprintCallable)
	void FreeLocation(const FVector& Location);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn System", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ASpawnTestActor> SpawnTestActorBlueprint;

	UPROPERTY()
	TMap<FVector, ASpawnTestActor*> OccupiedLocations;
};
