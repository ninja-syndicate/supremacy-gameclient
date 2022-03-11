// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Queue.h"
#include "UserAction.h"
#include "UserActionManager.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UUserActionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUserActionManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Checks whether an user action queue is empty. */
	UFUNCTION(BlueprintPure, Category = "User Action Queue")
	virtual bool IsQueueEmpty();

	/** Enqueues the user action to the queue. */
	UFUNCTION(BlueprintCallable, Category = "User Action Queue")
	virtual void EnqueueUserAction(const FUserAction& UserAction);

	/** Dequeues the user action from the queue. */
	UFUNCTION(BlueprintCallable, Category = "User Action Queue")
	virtual bool DequeueUserAction(FUserAction& OutUserAction);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TQueue<FUserAction> UserActionQueue;
};
