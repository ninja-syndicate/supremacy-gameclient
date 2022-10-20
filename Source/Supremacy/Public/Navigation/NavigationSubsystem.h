// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NavigationSubsystem.generated.h"

/**
 *
 */
UCLASS()
class SUPREMACY_API UNavigationSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UNavigationSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	// NOTE: Create a proxy actor that does replication if required.

	UFUNCTION(BlueprintPure)
	bool IsNavigable(const FVector& Location, const FVector& QueryExtent);

	UFUNCTION(BlueprintPure)
	bool GetDefaultQueryExtentByPawn(APawn* Pawn, FVector& OutDefaultQueryExtent);

	UFUNCTION(BlueprintPure)
	bool GetDefaultQueryExtent(FVector& OutDefaultQueryExtent);

	UFUNCTION(BlueprintPure)
	bool ProjectPointToNavigation(const FVector& Location, const FVector& QueryExtent, FVector& OutLocation);

	UFUNCTION(BlueprintCallable)
	bool GetBaseGroundLocation(const FVector& Location, FVector& OutLocation);

	/**
	 * Gets nearest navigable location from the given `Location`. Note that valid `OutLocation` is not necessarily traversable from the `Location`.
	 *
	 * @param Location The location to get the nearest navigable area from.
	 * @param OutLocation The nearest navigable location from the `Location`.
	 * @param AgentRadius The radius of the agent.
	 * @param AgentHeight The total height of the agent.
	 * @param bSearchUnbound By default, the search radius is bounded. Setting this to true will search unbounded. Enabling this option can cause big performance hits.
	 * @returns true if nearest navigable location is found and false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta = (AgentRadius = 500, AgentHeight = 1000, bSearchUnbound = false))
	bool GetNearestNavigableArea(const FVector& Location, FVector& OutLocation, float AgentRadius, float AgentHeight, bool bSearchUnbound);

	UFUNCTION(BlueprintCallable, meta = (bSearchUnbound = false))
	bool GetNearestNavigableAreaByPawn(APawn* Pawn, FVector& OutLocation, bool bSearchUnbound);

	UFUNCTION(BlueprintCallable, meta = (bSearchUnbound = false))
	bool GetNearestNavigableAreaByExtent(const FVector& Location, FVector& OutLocation, const FVector& DefaultQueryExtent, bool bSearchUnbound);

private:
	void OnPreBeginPlay();
	bool TraceByProfile(const FVector& StartLocation, const FVector& EndLocation, const FName& ProfileName, FVector& OutLocation);

	UPROPERTY(Category = "Navigation", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNavigationSystemV1> NavSys;

	/** Used as a fallback for determining ground location if there are no actors with Ground profile to serve as a base ground platform. */
	UPROPERTY(Category = "Navigation", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> FallbackAIPlayerStart;

	/** The name of the Ground profile that will be used for performing trace to figure out the base ground location. */
	UPROPERTY(Category = "Navigation", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName GroundProfileName;

	/** The name of the tag used to identify AI player starts. */
	UPROPERTY(Category = "Navigation", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName AIPlayerStartTagName;
};
