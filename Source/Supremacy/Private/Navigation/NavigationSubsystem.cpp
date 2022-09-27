// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/NavigationSubsystem.h"

#include "Landscape.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UNavigationSubsystem::UNavigationSubsystem() : Super()
{
	GroundProfileName = FName("Ground");
	AIPlayerStartTagName = FName("AI");
}

void UNavigationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UNavigationSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UNavigationSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	OnPreBeginPlay();
}

void UNavigationSubsystem::OnPreBeginPlay()
{
	TArray<AActor*> Landscapes;
	TArray<AActor*> AIPlayerStarts;

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNavigationSubsystem: Failed to get a Unreal navigation system!"));
		return;
	}

	// Get the landscapes and AI player starts in the current map to determine the base ground height.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), Landscapes);
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APlayerStart::StaticClass(), AIPlayerStartTagName, AIPlayerStarts);

	// Check for landscapes.
	if (Landscapes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("UNavigationSubsystem: No landscapes found in the current map."));
		UE_LOG(LogTemp, Warning, TEXT("UNavigationSubsystem: Note that you will need either some actor with Ground profile or player starts with AI tag to serve as a base ground platform."));
		UE_LOG(LogTemp, Warning, TEXT("UNavigationSubsystem: You can ignore this warning message if you already have this set up."));
	}

	// Check for AI player starts.
	if (AIPlayerStarts.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("UNavigationSubsystem: No player starts with AI tag found. This means AI player starts won't be used as a fallback in case there are no actors with Ground profile."));
	}
	else
	{
		FallbackAIPlayerStart = AIPlayerStarts[0];
	}
}

bool UNavigationSubsystem::IsNavigable(const FVector& Location)
{
	if (!NavSys) return false;

	FNavLocation ResultLocation;
	bool bProjectSuccess = NavSys->ProjectPointToNavigation(Location, ResultLocation, GetQueryExtent());
	return bProjectSuccess;
}

bool UNavigationSubsystem::GetBaseGroundLocation(const FVector& Location, FVector& OutLocation)
{
	// Perform trace by profile to Ground to find the base ground location along the `location`.
	FVector ResultLocation;
	const FVector StartLocation = Location + FVector::UpVector * 1000000.f;
	const FVector EndLocation = Location + FVector::DownVector * 1000000.f;
	
	bool IsHit = TraceByProfile(StartLocation, EndLocation, GroundProfileName, ResultLocation);
	if (IsHit)
	{
		OutLocation = ResultLocation;
		return true;
	}

	// Use the AI player start as a fallback to determine base ground Z-height.
	if (FallbackAIPlayerStart)
	{
		const float Height = FallbackAIPlayerStart->GetActorLocation().Z;

		OutLocation = FVector(Location.X, Location.Y, Height);
		return true;
	}

	// Cannot determine the base ground location.
	OutLocation = FVector::ZeroVector;
	return false;
}

bool UNavigationSubsystem::GetNearestNavigableArea(const FVector& Location, FVector& OutLocation, bool bSearchUnbound)
{
	if (!NavSys) return false;

	const int SearchIterationCount = bSearchUnbound ? 100 : 5;
	const float SearchRadiusDelta = 2500;

	// Test the given location to see if it's navigable.
	FNavLocation ResultLocation;
	bool bProjectSuccess = NavSys->ProjectPointToNavigation(Location, ResultLocation, GetQueryExtent());

	if (bProjectSuccess)
	{
		OutLocation = ResultLocation.Location;
		return true;
	}

	float CurrentSearchRadius = SearchRadiusDelta;
	if (CurrentSearchRadius <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNavigationComponent: Search radius delta is non-positive. Failed to search."));
		return false;
	}

	// Get random navigable point in radius from the given location, with increasing search radius.
	for (int32 i = 0; i < SearchIterationCount; ++i)
	{
		const bool bSearchSuccess = NavSys->GetRandomPointInNavigableRadius(Location, CurrentSearchRadius, ResultLocation);

		if (bSearchSuccess)
		{
			OutLocation = ResultLocation.Location;
			return true;
		}
		CurrentSearchRadius += SearchRadiusDelta;
	}
	// No valid location.
	return false;
}

FVector UNavigationSubsystem::GetQueryExtent() const
{
	// NOTE: The height needs to be high enough to also take account of jumping.
	return FVector(750, 750, 2000);
}

bool UNavigationSubsystem::TraceByProfile(const FVector& StartLocation, const FVector& EndLocation, const FName& ProfileName, FVector& OutLocation)
{
	FHitResult HitResult;
	
	bool IsHit = GetWorld()->LineTraceSingleByProfile(HitResult, StartLocation, EndLocation, ProfileName);
	if (!IsHit)
	{
		OutLocation = FVector::ZeroVector;
		return false;
	}

	OutLocation = HitResult.Location;
	return true;
}
