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

	// NOTE: Create a proxy actor that does replication if required.

	UFUNCTION(BlueprintCallable)
	bool IsNavigable(const FVector& Location);

	UFUNCTION(BlueprintCallable)
	bool GetBaseGroundLocation(const FVector& Location, FVector& OutLocation);

	UFUNCTION(BlueprintCallable)
	bool GetNearestNavigableArea(const FVector& Location, FVector& OutLocation);

	UFUNCTION(BlueprintCallable)
	FVector GetQueryExtent() const;

private:
	void OnBeginPlay();
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
