//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PoolSpawnOptions.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

#include "PooledActor.generated.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UObjectPool;
class UPooledProjectile;
class USharedObjectPool;
class UPooledSplineProjectile;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pooled Actor:: Actor Class Template

///  Pooled Object Template;
/// Actor type capable of being spawned as member of a Pool and automatically managed by the Pool Component.
UCLASS(ClassGroup = Synaptech, Category = "Performance", Blueprintable, BlueprintType, meta = (DisplayName = "Pool Actor", ShortTooltip = "Pool Actor Class."))
class OBJPOOL_API APooledActor : public AActor {
	GENERATED_UCLASS_BODY()
	//
	friend class UObjectPool;
	friend class UPooledProjectile;
	friend class USharedObjectPool;
	friend class UPooledSplineProjectile;
protected:
	/// Finishes Spawning this Actor, after deferred spawning from the Object-Pool.
	virtual void FinishSpawnFromPool(const bool Reconstruct, const FTransform &Transform);
	//
	//
	UPROPERTY()
	bool Spawned;
	//
	UPROPERTY()
	UObjectPool* OwningPool;
	//
	UPROPERTY()
	USharedObjectPool* SharedPool;
	//
	UPROPERTY()
	FTimerHandle LifeSpanHandle;
public:
	virtual void Initialize();
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//
	/// How long this Actor lives after Spawn from Pool. 0 = Forever.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0"))
	float LifeSpanPool;
	//
	//
	/// Event called every time this Actor is spawned from the Pool.
	UPROPERTY(Category="Object Pool", BlueprintAssignable)
	FOBJP_PoolEvent OnPoolBeginPlay;
	//
	/// Event called every time this Actor is sent back to the Pool.
	UPROPERTY(Category="Object Pool", BlueprintAssignable)
	FOBJP_PoolEvent OnPoolEndPlay;
	//
	//
	UFUNCTION()
	void SpawnFromPool(const bool Reconstruct, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform);
	//
	/// Returns this Pooled Actor to its owning Object-Pool, disabling it.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Return to Pool", Keywords="return actor pool"))
	void ReturnToPool();
	//
	/// Returns reference to the Pool Component owner of this Actor.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Owning Pool", Keywords="get owner pool"))
	UObjectPool* GetOwningPool() const;
	//
	/// Returns reference to the Shared Pool Component owner of this Actor, if any.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Shared Pool", Keywords="get shared pool"))
	USharedObjectPool* GetSharedPool() const;
	//
	//
	/// Sets Actor's Life Span from Pool. When it expires the object will be destroyed. If requested lifespan is 0, the timer is cleared and the actor will not be destroyed.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(Keywords="get life span"))
	virtual void SetLifeSpanPool(float InLifespan);
	//
	/// Gets Actor's remaining Life Span from Pool. If zero is returned the actor lives forever.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(Keywords="get life span"))
	virtual float GetLifeSpanPool() const;
	//
	//
	/// Event called every time this Actor is spawned from the Pool.
	UFUNCTION(Category="Object Pool", BlueprintNativeEvent, meta=(DisplayName="On Pool Begin Play", Keywords="pool begin play event"))
	void EVENT_OnPoolBeginPlay();
	//
	/// Event called every time this Actor is sent back to the Pool.
	UFUNCTION(Category="Object Pool", BlueprintNativeEvent, meta=(DisplayName="On Pool End Play", Keywords="pool end play event"))
	void EVENT_OnPoolEndPlay();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////