// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSystem/SpawnSubsystem.h"

#include "Landscape.h"
#include "NavigationSystem.h"
#include "NavModifierVolume.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DrawDebugHelpers.h"

USpawnSubsystem::USpawnSubsystem()
{
	DefaultNumDirections = 8;
	DefaultCollisionRadius = 600;
	DefaultSearchRadius = 100000;
}

void USpawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Bind the Setup method to the World BeginPlay event so that it gets called on BeginPlay.
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
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: No landscapes found in the current map. Some functionalities may fail."));
	}
	else
	{
		// For now, only get the first landscape as there is only one in every map.
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
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: No navigation system is found. Some functionalities may fail."));
	}

	// Get all the nav modifier volumes in the map. These will be ignored when testing collision.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavModifierVolume::StaticClass(), NavModifiers);
}

bool USpawnSubsystem::GetNearestEmptyLocation(
	FVector Origin,
	float CollisionRadius,
	float SearchRadius,
	TArray<AActor*> ActorsToIgnore,
	FVector& OutLocation,
	bool bGround,
	bool bNavigable)
{
	if (CollisionRadius <= 0)
	{
		CollisionRadius = DefaultCollisionRadius;
	}
	if (SearchRadius <= 0)
	{
		SearchRadius = DefaultSearchRadius;
	}
	if (bNavigable && !NavSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSubsystem: GetNearestEmptyLocation() failed as no nav mesh volume is found."));
		OutLocation = FVector::ZeroVector;
		return false;
	}
	// TODO: support multiple landscapes if required
	if (Landscape)
	{
		ActorsToIgnore.Add(Landscape);
	}
	// TODO: Allow option to decide whether to ignore nav modifiers or not.
	// For now, just ignore them.
	for (AActor* NavModifier : NavModifiers)
	{
		ActorsToIgnore.Add(NavModifier);
	}

	// Object types to consider.
	// TODO: Allow optional object type queries via paramater.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	//ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	// Test the origin point first for collision.
	bool IsSuccess;
	FVector NearestLocation;
	IsSuccess = TestLocation(Origin, bGround, bNavigable, CollisionRadius, SearchRadius, ObjectTypeQueries, ActorsToIgnore, NearestLocation);
	if (IsSuccess)
	{
		OutLocation = NearestLocation;
		return true;
	}

	// Otherwise, test different directions of increasing distance from the origin.
	const int NumDirections = DefaultNumDirections;
	for (float CurrentTestDistance = 500; CurrentTestDistance <= SearchRadius; CurrentTestDistance += 1000)
	{
		for (int i = 0; i < NumDirections; ++i)
		{
			const float CurrentAngle = 360.f * (i / static_cast<float>(NumDirections));
			const FVector CurrentDirection = FVector::ForwardVector.RotateAngleAxis(CurrentAngle, FVector::UpVector);
			const FVector NewCandidateLocation = Origin + CurrentDirection * CurrentTestDistance;

			IsSuccess = TestLocation(NewCandidateLocation, bGround, bNavigable, CollisionRadius, SearchRadius, ObjectTypeQueries, ActorsToIgnore, NearestLocation);
			if (IsSuccess)
			{
				OutLocation = NearestLocation;
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

bool USpawnSubsystem::TestLocation(
	FVector Location, 
	bool CheckGround, 
	bool NavigableArea,
	float DesiredRadius,
	float MaxDistance,
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries,
	TArray<AActor*> ActorsToIgnore,
	FVector& OutNearestLocation)
{
	// TODO: refactor this function a bit
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
			// TODO: Might not use random point in navigable radius if reachability is required.
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

	// HACK: adjust candidate Z location a bit to avoid colliding with static meshes on the floor
	CandidateLocation.Z += 1000;
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
	OutNearestLocation = CandidateLocation;
	return true;
}