// Fill out your copyright notice in the Description page of Project Settings.


#include "UserAction/UserActionManager.h"

// Sets default values for this component's properties
UUserActionManager::UUserActionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UUserActionManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UUserActionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UUserActionManager::IsQueueEmpty()
{
	return UserActionQueue.IsEmpty();
}

void UUserActionManager::EnqueueUserAction(const FUserAction& UserAction)
{
	UserActionQueue.Enqueue(UserAction);
}

bool UUserActionManager::DequeueUserAction(FUserAction& OutUserAction)
{
	return UserActionQueue.Dequeue(OutUserAction);
}