// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API USpawnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	USpawnSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn Subsystem")
	bool GetGroundLocation(FVector Origin, float Radius, FVector& OutLocation);

	/**
	 * Finds a nearest empty location around the specified origin.
	 *
	 * @param Origin The starting location to search for the nearest empty location.
	 * @param CollisionRadius The radius used for collision testing. Usually, this is radius of an actor to be spawned. If it is
	 * <= 0, default collision radius will be used.
	 * @param SearchRadius The maximum search radius to consider when searching. If it is <= 0, default search radius will be used.
	 * @param ActorsToIgnore Actors to ignore when searching.
	 * @param OutLocation The nearest empty location around the origin.
	 * @param bGround If true, OutLocation will be on ground. Otherwise, it may be in air.
	 * @param bNavigable If true, OutLocation will be inside navigation mesh, but not necessarily reachable to that area. 
	 * Usually, this is used for a pawn.
	 *	
	 * @return Returns true when such an empty location is found and false otherwise.
	 *
	 * @note This function can be pretty expensive. So, don't call it every frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Spawn Subsystem", meta = (AutoCreateRefTerm="ActorsToIgnore"))
	bool GetNearestEmptyLocation(
		FVector Origin,
		float CollisionRadius, 
		float SearchRadius,
		TArray<AActor*> ActorsToIgnore,
		FVector& OutLocation,
		bool bGround = true,
		bool bNavigable = true);
private:
	void OnPreBeginPlay();

	bool TestLocation(
		FVector Location, 
		bool CheckGround, 
		bool NavigableArea,
		float DesiredRadius,
		float MaxDistance,
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries,
		TArray<AActor*> ActorsToIgnore,
		FVector& OutNearestLocation);

	/** Debug flag used for visualisation. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	bool bEnableDebug;

	/** 
	 * The default number of directions to test for collision. 
	 * Higher the number, more likely to find good location, but more expensive. 
	 */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	int DefaultNumDirections;

	/** The default radius used for collision test. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	float DefaultCollisionRadius;

	/** The default max radius used for searching. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	float DefaultSearchRadius;

	/** Reference to the landscape in the current map if any. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	AActor* Landscape;

	/** Reference to the current navigation system if any. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	class UNavigationSystemV1* NavSys;

	/** A list of nav modifiers in the current map. */
	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> NavModifiers;
};
