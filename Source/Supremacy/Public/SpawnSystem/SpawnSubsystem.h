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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Get a nearest empty location around the origin.
	 *
	 * @param Origin The starting location to search for the nearest empty location.
	 * @param DesiredRadius The minimum desired radius of empty location. Usually, this is actor radius.
	 * @param MaxDistance The maximum distance to consider to search for the empty location.
	 * @param ActorsToIgnore Actors to ignore when finding an empty spawn location. Usually used to
	 * ignore actors that don't have visibility.
	 * @param bCheckGround If true, the empty location will be on ground. Otherwise, it may be mid-air.
	 * @param OutLocation The nearest empty location around the origin.
	 *	
	 * @return Returns true when such an empty location is found and false otherwise.
	 *
	 * @note This function can be pretty expensive. So, don't call it every frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Spawn Subsystem", meta = (AutoCreateRefTerm="ActorsToIgnore"))
	bool GetNearestEmptyLocation(
		FVector Origin,
		float DesiredRadius, 
		float MaxDistance,
		TArray<AActor*> ActorsToIgnore,
		FVector& OutLocation,
		bool bCheckGround = true,
		bool bNavigableArea = true);
private:
	void Setup();

	bool GetEmptyLocation(FVector Location, bool CheckGround, bool NavigableArea,
		float DesiredRadius,
		float MaxDistance,
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries,
		TArray<AActor*> ActorsToIgnore,
		FVector& OutLocation);

	bool GetGroundLocation(FVector Origin, FVector& OutLocation);

	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	bool bEnableDebug;

	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	AActor* Landscape;

	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	class UNavigationSystemV1* NavSys;

	UPROPERTY(EditAnywhere, Category = "Spawn Subsystem", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> NavModifiers;
};
