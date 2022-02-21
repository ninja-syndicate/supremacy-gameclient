//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PooledPawn.h"
#include "PooledActor.h"
#include "PooledCharacter.h"
#include "PooledProjectile.h"
#include "PoolSpawnOptions.h"
#include "PooledSplineProjectile.h"

#include "OBJPool.generated.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Template Pool Enumerators

UENUM(BlueprintType, meta=(DisplayName="Validation", Keywords="Spawn Validation"))
enum class FOBJPoolSpawning : uint8 {
	SpawnSuccessful,
	SpawnFailed
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Object Pool Component:: Stores Pooled Objects for Owner

/// Pool Data Component;
/// Builds and holds pointers to the data stored in memory to be used by Object-Pool Queries.
UCLASS(ClassGroup = Synaptech, Category="Performance", Blueprintable, BlueprintType, hideCategories = ("Activation", "Collision", "Sockets", "Variable"), meta=(BlueprintSpawnableComponent, DisplayName="Object-Pool Component", ShortTooltip = "Pool Data Class."))
class OBJPOOL_API UObjectPool : public UActorComponent {
	GENERATED_UCLASS_BODY()
	//
	friend class APooledActor;
protected:
	/// The Memory Pool.
	UPROPERTY()
	TArray<APooledActor*> Pool;
public:
	/// If enabled, every time the object is Pooled by the Pool, it's OnPoolBeginPlay() and OnPoolEndPlay() events will be executed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool ReinitializeInstances;
	//
	/// If enabled, a new object will be created by the Pool to fulfill the request from owner when there's no instances available;
	/// If disabled, nothing is instantiated if pool is empty and instead, resulting object returns NULL for the request out of bounds.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool InstantiateOnDemand;
	//
	/// If enabled, the Pool will guarantee that the 'Spawn Deferred' function will never fail with a null pointer.
	/// If there's no inactive Actor available then the function will point to the last spawned Actor instead.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool NeverFailDeferredSpawn;
	//
	/// If enabled, keeps alive Pooled Actors that are still active when the parent Pool Component has been destroyed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool KeepOrphanActorsAlive;
public:
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool", Keywords="initialize pool"))
	virtual void InitializeObjectPool();
	//
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool with Class [Template]", Keywords="initialize pool"))
	virtual void InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledActor> Template, const int32 SizeOfPool);
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//
	virtual void FlushObjectPool();
	//
	//
	/// The Actor Class needed to populate this Object-Pool.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APooledActor> TemplateClass;
	//
	/// How many instances you want to store pre-loaded.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 PoolSize = 1;
	//
	/// If checked, this will make this Pool Component to automatically load Object Instances when the Game starts.
	/// Initialization is still going to happen, independently, when a Pull request is received and the Pool is empty.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite)
	bool AutoInitialize;
	//
	UFUNCTION()
	void ReturnActor(APooledActor* PooledActor);
	//
	/// Will destroy all Pooled Actors stored by this Object-Pool.
	/// Note: A Pool Component, when destroyed, will also destroy all of its Pooled objects; Spawned or not.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Empty Object Pool", Keywords="empty delete pool"))
	void EmptyObjectPool();
	//
	//
	/// Returns the Container Array of Pooled Objects.
	/// WARNING: Danger! Do not manually Add or Remove members from this!
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Object Array", Keywords="get pool objects"))
	TArray<APooledActor*> GetObjectArray() const {return Pool;}
	//
	/// Fast-Query this Pool and returns all of its Spawned or Inactive Actors as separate lists.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Objects From Pool", Keywords="get pool objects"))
	void GetObjectsFromPool(TArray<APooledActor*> &Spawned, TArray<APooledActor*> &Inactive);
	//
	/// Fast-Query this Pool and returns all of its Spawned Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Objects", Keywords="get spawned objects"))
	void GetSpawnedObjects(TArray<APooledActor*> &Spawned);
	//
	/// Fast-Query this Pool and returns all of its Inactive Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Objects", Keywords="get inactive objects"))
	void GetInactiveObjects(TArray<APooledActor*> &Inactive);
	//
	/// Fast-Query this Pool and returns the first Spawned Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Object", Keywords="get pool spawned object"))
	APooledActor* GetSpawnedObject() const;
	//
	/// Fast-Query this Pool and returns the first Inactive Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Object", Keywords="get pool inactive object"))
	APooledActor* GetInactiveObject() const;
	//
	//
	/// Spawns an Actor from Pool, manually running its Construction Scripts if a full reset is needed.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledActor* BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UObjectPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful);
	//
	/// Finishes Deferred Spawning an Actor from Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledActor* FinishDeferredSpawnFromPool(APooledActor* Actor, const bool Reconstruct, const FTransform &SpawnTransform);
	//
	//
	/// Gets this Pool's Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetObjectsFromPool() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Spawned Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetSpawnedObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&O->Spawned) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Inactive Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetInactiveObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&(!O->Spawned)) {TC.Add(O);}
	} return TC;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pawn Pool Component:: Stores Pooled Pawn Actors for Owner

/// Pool Data Component;
/// Builds and holds pointers to the data stored in memory to be used by Object-Pool Queries.
UCLASS(ClassGroup = Synaptech, Category="Performance", Blueprintable, BlueprintType, hideCategories = ("Activation", "Collision", "Sockets", "Variable"), meta=(BlueprintSpawnableComponent, DisplayName="Pawn-Pool Component", ShortTooltip = "Pool Data Class."))
class OBJPOOL_API UPawnPool : public UActorComponent {
	GENERATED_UCLASS_BODY()
	//
	friend class APooledPawn;
protected:
	/// The Memory Pool.
	UPROPERTY()
	TArray<APooledPawn*> Pool;
public:
	/// If enabled, every time the object is Pooled by the Pool, it's OnPoolBeginPlay() and OnPoolEndPlay() events will be executed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool ReinitializeInstances;
	//
	/// If enabled, a new object will be created by the Pool to fulfill the request from owner when there's no instances available;
	/// If disabled, nothing is instantiated if pool is empty and instead, resulting object returns NULL for the request out of bounds.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool InstantiateOnDemand;
	//
	/// If enabled, the Pool will guarantee that the 'Spawn Deferred' function will never fail with a null pointer.
	/// If there's no inactive Actor available then the function will point to the last spawned Actor instead.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool NeverFailDeferredSpawn;
	//
	/// If enabled, keeps alive Pooled Actors that are still active when the parent Pool Component has been destroyed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool KeepOrphanActorsAlive;
public:
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool", Keywords="initialize pool"))
	virtual void InitializeObjectPool();
	//
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool with Class [Template]", Keywords="initialize pool"))
	virtual void InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledPawn> Template, const int32 SizeOfPool);
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//
	virtual void FlushObjectPool();
	//
	//
	/// The Actor Class needed to populate this Object-Pool.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APooledPawn> TemplateClass;
	//
	/// How many instances you want to store pre-loaded.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 PoolSize = 1;
	//
	/// If checked, this will make this Pool Component to automatically load Object Instances when the Game starts.
	/// Initialization is still going to happen, independently, when a Pull request is received and the Pool is empty.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite)
	bool AutoInitialize;
	//
	UFUNCTION()
	void ReturnActor(APooledPawn* PooledActor);
	//
	/// Will destroy all Pooled Actors stored by this Object-Pool.
	/// Note: A Pool Component, when destroyed, will also destroy all of its Pooled objects; Spawned or not.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Empty Object Pool", Keywords="empty delete pool"))
	void EmptyObjectPool();
	//
	//
	/// Returns the Container Array of Pooled Objects.
	/// WARNING: Danger! Do not manually Add or Remove members from this!
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Object Array", Keywords="get pool objects"))
	TArray<APooledPawn*> GetObjectArray() const {return Pool;}
	//
	/// Fast-Query this Pool and returns all of its Spawned or Inactive Actors as separate lists.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Objects From Pool", Keywords="get pool objects"))
	void GetObjectsFromPool(TArray<APooledPawn*> &Spawned, TArray<APooledPawn*> &Inactive);
	//
	/// Fast-Query this Pool and returns all of its Spawned Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Objects", Keywords="get spawned objects"))
	void GetSpawnedObjects(TArray<APooledPawn*> &Spawned);
	//
	/// Fast-Query this Pool and returns all of its Inactive Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Objects", Keywords="get inactive objects"))
	void GetInactiveObjects(TArray<APooledPawn*> &Inactive);
	//
	/// Fast-Query this Pool and returns the first Spawned Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Object", Keywords="get pool spawned object"))
	APooledPawn* GetSpawnedObject() const;
	//
	/// Fast-Query this Pool and returns the first Inactive Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Object", Keywords="get pool inactive object"))
	APooledPawn* GetInactiveObject() const;
	//
	//
	/// Spawns an Actor from Pool, manually running its Construction Scripts if a full reset is needed.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledPawn* BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UPawnPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful);
	//
	/// Finishes Deferred Spawning an Actor from Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledPawn* FinishDeferredSpawnFromPool(APooledPawn* Pawn, const bool Reconstruct, const FTransform &SpawnTransform);
	//
	//
	/// Gets this Pool's Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetObjectsFromPool() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Spawned Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetSpawnedObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&O->Spawned) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Inactive Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetInactiveObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&(!O->Spawned)) {TC.Add(O);}
	} return TC;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Character Pool Component:: Stores Pooled Character Actors for Owner

/// Pool Data Component;
/// Builds and holds pointers to the data stored in memory to be used by Object-Pool Queries.
UCLASS(ClassGroup = Synaptech, Category="Performance", Blueprintable, BlueprintType, hideCategories = ("Activation", "Collision", "Sockets", "Variable"), meta=(BlueprintSpawnableComponent, DisplayName="Character-Pool Component", ShortTooltip = "Pool Data Class."))
class OBJPOOL_API UCharacterPool : public UActorComponent {
	GENERATED_UCLASS_BODY()
	//
	friend class APooledCharacter;
protected:
	/// The Memory Pool.
	UPROPERTY()
	TArray<APooledCharacter*> Pool;
public:
	/// If enabled, every time the object is Pooled by the Pool, it's OnPoolBeginPlay() and OnPoolEndPlay() events will be executed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool ReinitializeInstances;
	//
	/// If enabled, a new object will be created by the Pool to fulfill the request from owner when there's no instances available;
	/// If disabled, nothing is instantiated if pool is empty and instead, resulting object returns NULL for the request out of bounds.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool InstantiateOnDemand;
	//
	/// If enabled, the Pool will guarantee that the 'Spawn Deferred' function will never fail with a null pointer.
	/// If there's no inactive Actor available then the function will point to the last spawned Actor instead.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool NeverFailDeferredSpawn;
	//
	/// If enabled, keeps alive Pooled Actors that are still active when the parent Pool Component has been destroyed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool KeepOrphanActorsAlive;
public:
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool", Keywords="initialize pool"))
	virtual void InitializeObjectPool();
	//
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool with Class [Template]", Keywords="initialize pool"))
	virtual void InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledCharacter> Template, const int32 SizeOfPool);
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//
	virtual void FlushObjectPool();
	//
	//
	/// The Actor Class needed to populate this Object-Pool.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APooledCharacter> TemplateClass;
	//
	/// How many instances you want to store pre-loaded.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 PoolSize = 1;
	//
	/// If checked, this will make this Pool Component to automatically load Object Instances when the Game starts.
	/// Initialization is still going to happen, independently, when a Pull request is received and the Pool is empty.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite)
	bool AutoInitialize;
	//
	UFUNCTION()
	void ReturnActor(APooledCharacter* PooledActor);
	//
	/// Will destroy all Pooled Actors stored by this Object-Pool.
	/// Note: A Pool Component, when destroyed, will also destroy all of its Pooled objects; Spawned or not.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Empty Object Pool", Keywords="empty delete pool"))
	void EmptyObjectPool();
	//
	//
	/// Returns the Container Array of Pooled Objects.
	/// WARNING: Danger! Do not manually Add or Remove members from this!
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Object Array", Keywords="get pool objects"))
	TArray<APooledCharacter*> GetObjectArray() const {return Pool;}
	//
	/// Fast-Query this Pool and returns all of its Spawned or Inactive Actors as separate lists.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Objects From Pool", Keywords="get pool objects"))
	void GetObjectsFromPool(TArray<APooledCharacter*> &Spawned, TArray<APooledCharacter*> &Inactive);
	//
	/// Fast-Query this Pool and returns all of its Spawned Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Objects", Keywords="get spawned objects"))
	void GetSpawnedObjects(TArray<APooledCharacter*> &Spawned);
	//
	/// Fast-Query this Pool and returns all of its Inactive Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Objects", Keywords="get inactive objects"))
	void GetInactiveObjects(TArray<APooledCharacter*> &Inactive);
	//
	/// Fast-Query this Pool and returns the first Spawned Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Object", Keywords="get pool spawned object"))
	APooledCharacter* GetSpawnedObject() const;
	//
	/// Fast-Query this Pool and returns the first Inactive Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Object", Keywords="get pool inactive object"))
	APooledCharacter* GetInactiveObject() const;
	//
	//
	/// Spawns an Actor from Pool, manually running its Construction Scripts if a full reset is needed.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledCharacter* BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UCharacterPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful);
	//
	/// Finishes Deferred Spawning an Actor from Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction = "true", BlueprintInternalUseOnly = "true"))
	static APooledCharacter* FinishDeferredSpawnFromPool(APooledCharacter* Character, const bool Reconstruct, const FTransform &SpawnTransform);
	//
	//
	/// Gets this Pool's Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetObjectsFromPool() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Spawned Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetSpawnedObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&O->Spawned) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Inactive Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetInactiveObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&(!O->Spawned)) {TC.Add(O);}
	} return TC;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Shared Object Pool Component:: Stores Pooled Objects for Owner

/// Pool Data Component;
/// Builds and holds pointers to the data stored in memory to be used by Object-Pool Queries.
UCLASS(ClassGroup = Synaptech, Category="Performance", Blueprintable, BlueprintType, hideCategories = ("Activation", "Collision", "Sockets", "Variable"), meta=(BlueprintSpawnableComponent, DisplayName="Shared-Pool Component", ShortTooltip = " Shared Pool Data Class."))
class OBJPOOL_API USharedObjectPool : public UActorComponent {
	GENERATED_UCLASS_BODY()
	//
	friend class APooledActor;
protected:
	/// The Memory Pool.
	UPROPERTY()
	TArray<APooledActor*> Pool;
public:
	/// If enabled, every time the object is Pooled by the Pool, it's OnPoolBeginPlay() and OnPoolEndPlay() events will be executed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool ReinitializeInstances;
	//
	/// If enabled, a new object will be created by the Pool to fulfill the request from owner when there's no instances available;
	/// If disabled, nothing is instantiated if pool is empty and instead, resulting object returns NULL for the request out of bounds.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool InstantiateOnDemand;
	//
	/// If enabled, the Pool will guarantee that the 'Spawn Deferred' function will never fail with a null pointer.
	/// If there's no inactive Actor available then the function will point to the last spawned Actor instead.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool NeverFailDeferredSpawn;
	//
	/// If enabled, keeps alive Pooled Actors that are still active when the parent Pool Component has been destroyed.
	UPROPERTY(Category="Object Pool", AdvancedDisplay, EditAnywhere, BlueprintReadOnly)
	bool KeepOrphanActorsAlive;
public:
	virtual void FlushObjectPool();
	//
	/// Empties the Pool; Respawns all of its members based on 'Pool Size' allocation.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Initialize Object Pool", Keywords="initialize pool"))
	void InitializeObjectPool();
public:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//
	//
	/// If checked, this will make this Pool Component to automatically load Object Instances when the Game starts.
	/// Initialization is still going to happen, independently, when a Pull request is received and the Pool is empty.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadWrite)
	bool AutoInitialize;
	//
	/// The Template Classes used to populate this Object-Pool.
	UPROPERTY(Category="Object Pool", EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<APooledActor>,int32> TemplateClasses;
	//
	//
	UFUNCTION()
	void ReturnActor(APooledActor* PooledActor);
	//
	/// Will destroy all Pooled Actors of Class stored by this Object-Pool.
	/// Note: A Pool Component, when destroyed, will also destroy all of its Pooled objects; Spawned or not.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Empty Object Pool", Keywords="empty delete pool"))
	void EmptyObjectPool(const UClass* Class);
	//
	//
	/// Returns the Container Array of Pooled Objects.
	/// WARNING: Danger! Do not manually Add or Remove members from this!
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Object Array", Keywords="get pool objects"))
	TArray<APooledActor*> GetObjectArray() const {return Pool;}
	//
	/// Fast-Query this Pool and returns all of its Spawned or Inactive Actors as separate lists.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Objects From Pool", Keywords="get pool objects"))
	void GetObjectsFromPool(const UClass* Class, TArray<APooledActor*> &Spawned, TArray<APooledActor*> &Inactive);
	//
	/// Fast-Query this Pool and returns all of its Spawned Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Objects", Keywords="get spawned objects"))
	void GetSpawnedObjects(const UClass* Class, TArray<APooledActor*> &Spawned);
	//
	/// Fast-Query this Pool and returns all of its Inactive Actors list.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Objects", Keywords="get inactive objects"))
	void GetInactiveObjects(const UClass* Class, TArray<APooledActor*> &Inactive);
	//
	/// Fast-Query this Pool and returns the first Spawned Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Spawned Object", Keywords="get pool spawned object"))
	APooledActor* GetSpawnedObject(const UClass* Class) const;
	//
	/// Fast-Query this Pool and returns the first Inactive Actor found on top of the Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(DisplayName="Get Inactive Object", Keywords="get pool inactive object"))
	APooledActor* GetInactiveObject(const UClass* Class) const;
	//
	//
	/// Spawns an Actor from Pool, manually running its Construction Scripts if a full reset is needed.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true", BlueprintInternalUseOnly="true"))
	static APooledActor* BeginDeferredSpawnFromPool(const UObject* WorldContextObject, USharedObjectPool* SharedPool, UClass* Class, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful);
	//
	/// Finishes Deferred Spawning an Actor from Pool.
	UFUNCTION(Category="Object Pool", BlueprintCallable, meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true", BlueprintInternalUseOnly="true"))
	static APooledActor* FinishDeferredSpawnFromPool(APooledActor* Actor, const bool Reconstruct, const FTransform &SpawnTransform);
	//
	//
	/// Gets this Pool's Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetObjectsFromPool() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Spawned Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetSpawnedObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&O->Spawned) {TC.Add(O);}
	} return TC;}
	//
	/// Gets this Pool's Inactive Objects, Type-casting.
	/// Returns Empty Array if Cast fails.
	template <typename T>
	FORCEINLINE TArray<T*> GetInactiveObjects() const {
		TArray<T*> TC;
		for (const auto &OBJ : Pool) {
			if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
			T* O = Cast<T>(*&OBJ); if (O&&(!O->Spawned)) {TC.Add(O);}
	} return TC;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LOG_OBJ(const bool Debug, const float Duration, const FColor Color, const FString Message);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////