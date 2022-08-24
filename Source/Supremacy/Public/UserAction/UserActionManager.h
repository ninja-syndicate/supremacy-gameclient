// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Queue.h"
#include "UserAction.h"
#include "Types/AbilityID.h"
#include "UserActionManager.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UUserActionManager final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUserActionManager();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnAbility(const EAbilityID Ability, const FVector2D Location, const FVector2D LocationEnd, const FString& EventID, const FString& TriggeredByUserID, const FString& TriggeredByUsername, const FString& WarMachineHash, const FString& FactionID);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUserActionDispatched, AActor*, Actor, const FString&, Tag, const FString&, EventID, const FString&, InstigatorFactionID);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
		FUserActionDispatched UserActionDispatched;
	
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
private:
	TQueue<FUserAction> UserActionQueue;
};
