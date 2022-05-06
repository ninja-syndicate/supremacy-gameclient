// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAction/Nuke/NukeExplosion.h"

// Sets default values
ANukeExplosion::ANukeExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANukeExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANukeExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

