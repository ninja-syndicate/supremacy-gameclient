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

bool UNavigationSubsystem::IsNavigable(const FVector& Location, const FVector& QueryExtent)
{
	FVector OutLocation;
	return ProjectPointToNavigation(Location, QueryExtent, OutLocation);
}

bool UNavigationSubsystem::GetDefaultQueryExtentByPawn(APawn* Pawn, FVector& OutDefaultQueryExtent)
{
	if (!NavSys) return false;
	if (!IsValid(Pawn)) return false;

	const FNavAgentProperties& NavAgentProps = Pawn->GetNavAgentPropertiesRef();
	const ANavigationData* NavData = NavSys->GetNavDataForProps(NavAgentProps);
	if (!NavData) return false;

	OutDefaultQueryExtent = NavData->GetDefaultQueryExtent();
	return true;
}

bool UNavigationSubsystem::GetDefaultQueryExtent(FVector& OutDefaultQueryExtent)
{
	if (!NavSys) return false;

	const ANavigationData* NavData = NavSys->GetDefaultNavDataInstance();
	if (!NavData) return false;

	OutDefaultQueryExtent = NavData->GetDefaultQueryExtent();
	return true;
}

bool UNavigationSubsystem::ProjectPointToNavigation(const FVector& Location, const FVector& QueryExtent, FVector& OutLocation)
{
	if (!NavSys) return false;

	FNavLocation ResultLocation;
	const bool bProjectSucceed = NavSys->ProjectPointToNavigation(Location, ResultLocation, QueryExtent);
	if (!bProjectSucceed) return false;
	
	OutLocation = ResultLocation.Location;
	return true;
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

bool UNavigationSubsystem::GetNearestNavigableArea(const FVector& Location, FVector& OutLocation, float AgentRadius, float AgentHeight, bool bSearchUnbound)
{
	if (!NavSys) return false;
	
	// Make nav agent props for query extent testing.
	FNavAgentProperties NavAgentProps;
	NavAgentProps.AgentRadius = AgentRadius;
	NavAgentProps.AgentHeight = AgentHeight;
	NavAgentProps.NavWalkingSearchHeightScale = FNavigationSystem::GetDefaultSupportedAgent().NavWalkingSearchHeightScale;

	// Test the given location to see if it's navigable.
	FNavLocation ResultLocation;
	bool bProjectSuccess = NavSys->ProjectPointToNavigation(Location, ResultLocation, INVALID_NAVEXTENT, &NavAgentProps);

	if (bProjectSuccess)
	{
		OutLocation = ResultLocation.Location;
		return true;
	}

	const int SearchIterationCount = bSearchUnbound ? 100 : 5;
	const float SearchRadiusDelta = 2500;

	float CurrentSearchRadius = SearchRadiusDelta;
	if (CurrentSearchRadius <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNavigationComponent: Search radius delta is non-positive. Failed to search."));
		return false;
	}

	// Get the nav data associated with the nav agent props.
	ANavigationData* NavData = NavSys->GetNavDataForProps(NavAgentProps);

	// Get random navigable point in radius from the given location, with increasing search radius.
	for (int32 i = 0; i < SearchIterationCount; ++i)
	{
		const bool bSearchSuccess = NavSys->GetRandomPointInNavigableRadius(Location, CurrentSearchRadius, ResultLocation, NavData);

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

bool UNavigationSubsystem::GetNearestNavigableAreaByPawn(APawn* Pawn, FVector& OutLocation, bool bSearchUnbound)
{
	if (!IsValid(Pawn)) return false;

	FVector DefaultQueryExtent;

	const bool bSuccess = GetDefaultQueryExtentByPawn(Pawn, DefaultQueryExtent);
	if (bSuccess) return false;

	return GetNearestNavigableAreaByExtent(Pawn->GetActorLocation(), OutLocation, DefaultQueryExtent, bSearchUnbound);
}

bool UNavigationSubsystem::GetNearestNavigableAreaByExtent(const FVector& Location, FVector& OutLocation, const FVector& DefaultQueryExtent, bool bSearchUnbound)
{
	const float AgentRadius = DefaultQueryExtent.X;
	const float AgentHeight = DefaultQueryExtent.Z;
	return GetNearestNavigableArea(Location, OutLocation, AgentRadius, AgentHeight, bSearchUnbound);
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
