// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSystem/SpawnSubsystem.h"

#include "Landscape.h"
#include "NavModifierVolume.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DrawDebugHelpers.h"

void USpawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Bind the Setup method to the World BeginPlay event.
	GetWorld()->OnWorldBeginPlay.AddUObject(this, &USpawnSubsystem::Setup);
}

void USpawnSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void USpawnSubsystem::Setup()
{
	// Get the landscapes in the current map.
	TArray<AActor*> Landscapes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), Landscapes);
	if (Landscapes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: No landscape found in the current map. Some things related to spawning may fail..."));
	}
	else
	{
		// For now, get only the first landscape as there is only one in every map.
		Landscape = Landscapes[0];
		if (Landscapes.Num() > 1) 
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: Multiple landscapes detected. SpawnSubsystem will need to be changed to support it."));
		}
	}

	// Get the navigation system and set the reference to it.
	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: No navigation mesh volume is found. Some things related to nav mesh may fail..."));
	}

	// Get all the nav modifiers to ignore.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavModifierVolume::StaticClass(), NavModifiers);
}

bool USpawnSubsystem::GetNearestEmptyLocation(
	FVector Origin,
	float DesiredRadius,
	float MaxDistance,
	TArray<AActor*> ActorsToIgnore,
	FVector& OutLocation,
	bool bCheckGround,
	bool bNavigableArea)
{
	if (bNavigableArea && !NavSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: GetNearestEmptyLocation() failed as no nav mesh volume is found."));
		OutLocation = FVector::ZeroVector;
		return false;
	}
	// TODO: support multiple if required
	if (Landscape)
	{
		ActorsToIgnore.Add(Landscape);
	}
	for (AActor* NavModifier : NavModifiers)
	{
		ActorsToIgnore.Add(NavModifier);
	}

	// Object types to consider.
	// TODO: Allow optional object type queries via paramater.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	// ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	// Try the origin point first.
	FVector EmptyLocation;
	bool IsEmpty = GetEmptyLocation(Origin, bCheckGround, bNavigableArea, DesiredRadius, MaxDistance, ObjectTypeQueries, ActorsToIgnore, EmptyLocation);
	if (IsEmpty)
	{
		// Adjust Z height a bit to avoid falling through the floor.
		EmptyLocation.Z += 1000.f;
		OutLocation = EmptyLocation;
		return true;
	}

	// Otherwise, try different directions of increasing distance from the origin.
	const int NumDirections = 8;
	for (float CurrentTestDistance = 500; CurrentTestDistance <= MaxDistance; CurrentTestDistance += 1000)
	{
		for (int i = 0; i < NumDirections; ++i)
		{
			const float CurrentAngle = 360.f * (i / static_cast<float>(NumDirections));
			const FVector CurrentDirection = FVector::ForwardVector.RotateAngleAxis(CurrentAngle, FVector::UpVector);
			const FVector NewCandidateLocation = Origin + CurrentDirection * CurrentTestDistance;

			FVector NewEmptyLocation;
			bool IsNewCandidateEmpty = GetEmptyLocation(NewCandidateLocation, bCheckGround, bNavigableArea, DesiredRadius, MaxDistance, ObjectTypeQueries, ActorsToIgnore, NewEmptyLocation);
			if (IsNewCandidateEmpty)
			{
				// Adjust Z height a bit to avoid falling through the floor.
				NewEmptyLocation.Z += 1000.f;
				OutLocation = NewEmptyLocation;
				return true;
			}
		}
	}
	OutLocation = FVector::ZeroVector;
	return false;
}

bool USpawnSubsystem::GetGroundLocation(FVector Origin, FVector& OutLocation)
{
	FHitResult HitResult;
	FVector OriginHigh = Origin + FVector::UpVector * 1000000.f;
	FVector OriginLow = Origin + FVector::DownVector * 1000000.f;

	ECollisionChannel LevelChannel = ECC_GameTraceChannel4;

	// TODO: Make a function that can be used to get the landscape ground level.
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, OriginHigh, OriginLow, LevelChannel);
	if (!IsHit)
	{
		OutLocation = FVector::ZeroVector;
		return false;
	}
	OutLocation = HitResult.Location;
	return true;
}

bool USpawnSubsystem::GetEmptyLocation(FVector Location, bool CheckGround, bool NavigableArea,
	float DesiredRadius,
	float MaxDistance,
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries,
	TArray<AActor*> ActorsToIgnore,
	FVector& OutLocation)
{
	FVector CandidateLocation = Location;
	FVector DebugLocation = FVector(Location.X, Location.Y, Location.Z + 100000);
	if (CheckGround)
	{
		FVector GroundLocation;
		bool IsSuccess = GetGroundLocation(CandidateLocation, GroundLocation);
		if (!IsSuccess)
		{
			if (bEnableDebug)
			{
				DrawDebugLine(GetWorld(), DebugLocation, GroundLocation, FColor(255, 0, 0), false, -1, 0, 50);
			}
			return false;
		}

		CandidateLocation = GroundLocation;
	}
	bool IsNavLocation = false;
	bool HasNearestPoint = false;
	if (NavigableArea)
	{
		FNavLocation NavLoc;
		FVector QueryingExtent = FVector(50.0f, 50.0f, 500.0f);
		IsNavLocation = NavSys->ProjectPointToNavigation(CandidateLocation, NavLoc, QueryingExtent);
		if (!IsNavLocation)
		{
			// Might not use random point in navigable radius if reachability is required.
			FNavLocation NearestNavLocation;
			HasNearestPoint = NavSys->GetRandomPointInNavigableRadius(CandidateLocation, 1000, NearestNavLocation);
			if (!HasNearestPoint)
			{
				if (bEnableDebug)
				{
					DrawDebugLine(GetWorld(), DebugLocation, CandidateLocation, FColor(0, 0, 255), true, -1, 0, 50);
				}
				return false;
			}

			CandidateLocation = NearestNavLocation;
		}
		else
		{
			CandidateLocation = NavLoc.Location;
		}
	}
	if (NavigableArea && !IsNavLocation && !HasNearestPoint)
		return false;

	// HACK: adjust candidate location a bit
	CandidateLocation.Z += 600;
	TArray<AActor*> OverlappingActors;
	bool IsOverlapping = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), CandidateLocation, DesiredRadius, ObjectTypeQueries, nullptr, ActorsToIgnore, OverlappingActors);
	if (IsOverlapping)
	{
		if (bEnableDebug)
		{
			DrawDebugLine(GetWorld(), DebugLocation, CandidateLocation, FColor(0, 0, 0), true, -1, 0, 50);
			for (AActor* Actor : OverlappingActors)
			{
				const FString Name = UKismetSystemLibrary::GetDisplayName(Actor);
				UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *Name);
			}
		}
		int Count = 0;
		for (AActor* Actor : OverlappingActors)
		{
			// Some actors are world static, but not visible, so ignore those.
			// TODO: provide option to decide whether to ignore non-visible ones or not.
			ECollisionResponse Response = Actor->GetComponentsCollisionResponseToChannel(ECollisionChannel::ECC_Visibility);
			if (Response == ECollisionResponse::ECR_Ignore)
				++Count;
		}
		if (bEnableDebug)
		{
			UE_LOG(LogTemp, Warning, TEXT("Non-visible Count: %d, Overlapping Count: %d"), Count, OverlappingActors.Num());
		}
		if (Count != OverlappingActors.Num())
		{
			return false;
		}
	}
	if (bEnableDebug)
	{
		DrawDebugLine(GetWorld(), DebugLocation, CandidateLocation, FColor(0, 255, 0), true, -1, 0, 50);
	}
	OutLocation = CandidateLocation;
	return true;
}