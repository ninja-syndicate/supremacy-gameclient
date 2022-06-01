// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSystem/SpawnSystem.h"

#include "SpawnSystem/SpawnTestActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnSystem::USpawnSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpawnSystem::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USpawnSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* USpawnSystem::GetClosestActorWithTag(FVector Location, FName Tag, bool& OutSuccess)
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, Actors);
	
	// Find the actor with the minimum distance from the specified location.
	float MinDistance = INFINITY;
	AActor* ClosestActor = nullptr;
	for (int32 i = 0; i < Actors.Num(); ++i)
	{
		if (!IsValid(Actors[i]))
			continue;

		const float Distance = (Actors[i]->GetActorLocation() - Location).Size();
		if (Distance < MinDistance) 
		{
			ClosestActor = Actors[i];
			MinDistance = Distance;
		}
	}
	OutSuccess = ClosestActor != nullptr;
	return ClosestActor;
}

void USpawnSystem::OccupyLocation(const FVector& Location, float Radius)
{
	if (OccupiedLocations.Contains(Location))
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSystem: %s"), "Specified location is already occupied.");
		return;
	}
	// Use the spawn test actor blueprint if set, otherwise use the C++ actor.
	UClass* SpawnTestActorClass;
	if (SpawnTestActorBlueprint)
	{
		SpawnTestActorClass = SpawnTestActorBlueprint;
	} else {
		SpawnTestActorClass = ASpawnTestActor::StaticClass();
	}

    const FTransform SpawnTransform{Location};
    ASpawnTestActor* SpawnTestActor = GetWorld()->SpawnActorDeferred<ASpawnTestActor>(
        SpawnTestActorClass,
        SpawnTransform);
    SpawnTestActor->Initialize(Radius);
    SpawnTestActor->FinishSpawning(SpawnTransform);
	OccupiedLocations.Add(Location, SpawnTestActor);
}

void USpawnSystem::FreeLocation(const FVector& Location)
{
	if (!OccupiedLocations.Contains(Location))
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnSystem: %s"), "Attempted to free the location that is not occupied.");
		return;
	}
	OccupiedLocations.Remove(Location);
}
