// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSystem/SpawnTestActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASpawnTestActor::ASpawnTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);

	Radius = 100.f;
	CollisionComponent->SetSphereRadius(Radius);

	// TODO: Also set the collision channel here?
}

// Called when the game starts or when spawned
void ASpawnTestActor::BeginPlay()
{
	Super::BeginPlay();

	Radius = CollisionComponent->GetScaledSphereRadius();
}

// Called every frame
void ASpawnTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnTestActor::Initialize(float InRadius)
{
	Radius = InRadius;
	CollisionComponent->SetSphereRadius(InRadius);
}