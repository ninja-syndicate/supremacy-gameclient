//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OBJPool.h"
#include "OBJPool_Shared.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Object Pool Component Functions

UObjectPool::UObjectPool(const FObjectInitializer &OBJ) : Super(OBJ) {
	TemplateClass = APooledActor::StaticClass();
	SetComponentTickEnabled(false);
	SetActive(true,false);
	//
	bWantsInitializeComponent = true;
	NeverFailDeferredSpawn = false;
	KeepOrphanActorsAlive = false;
	ReinitializeInstances = true;
	InstantiateOnDemand = false;
	AutoInitialize = true;
}

void UObjectPool::BeginPlay() {
	Super::BeginPlay();
	//
	if (AutoInitialize) {InitializeObjectPool();}
}

void UObjectPool::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (!KeepOrphanActorsAlive) {EmptyObjectPool();}
	else {
		for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
			if (Pool[ID]->Spawned) {continue;}
			Pool[ID]->Destroy(true,true);
		}///
	}///
	//
	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UObjectPool::InitializeObjectPool() {
	if (TemplateClass==nullptr) {
		LOG_OBJ(true,5.f,FColor::Red,GetNameSafe(this)+FString(" : ")+FString("Invalid Template Class!"));
	return;} EmptyObjectPool();
	//
	FTransform SpawnTransform(FRotator::ZeroRotator,FVector::ZeroVector,FVector(1.f,1.f,1.f));
	for (int32 I=0; I<PoolSize; I++) {
		const auto &ACT = GetWorld()->SpawnActorDeferred<APooledActor>(TemplateClass,SpawnTransform,this->GetOwner(),GetOwner()->GetInstigator(),ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (ACT) {
			ACT->SharedPool = nullptr;
			ACT->OwningPool = const_cast<UObjectPool*>(this);
			ACT->FinishSpawning(SpawnTransform);
	ACT->Initialize();}}
	//
	FlushObjectPool();
}

void UObjectPool::InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledActor> Template, const int32 SizeOfPool) {
	TemplateClass = Template;
	PoolSize = SizeOfPool;
	//
	InitializeObjectPool();
}

void UObjectPool::FlushObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {Pool.RemoveAt(ID,1,false);}
	}///
}

void UObjectPool::EmptyObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (Pool[ID]->IsValidLowLevelFast()) {Pool[ID]->Destroy(true,true);}
	} Pool.Empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledActor* UObjectPool::BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UObjectPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful) {
	if (!ObjectPool->IsValidLowLevelFast()||ObjectPool->IsPendingKill()||ObjectPool->GetOwner()==nullptr||PooledClass==nullptr) {return nullptr;}
	//
	if (ObjectPool->TemplateClass.Get() != PooledClass) {
		LOG_OBJ(true,5.f,FColor::Red,ObjectPool->GetName()+FString(" : ")+FString::Printf(TEXT("Requested Class(%s) not implemented by this Pool. Check the value of 'Template Class' on the Pool Component."),*PooledClass->GetName()));
	return nullptr;}
	//
	if (ObjectPool->Pool.Num()==0) {ObjectPool->InitializeObjectPool();}
	APooledActor* DeferredSpawn = ObjectPool->GetInactiveObject();
	//
	if ((DeferredSpawn==nullptr) && ObjectPool->InstantiateOnDemand) {
		DeferredSpawn = ObjectPool->GetWorld()->SpawnActorDeferred<APooledActor>(ObjectPool->TemplateClass,SpawnTransform,Owner,ObjectPool->GetOwner()->GetInstigator(),CollisionHandlingOverride);
		if (DeferredSpawn) {DeferredSpawn->SharedPool = nullptr; DeferredSpawn->OwningPool = ObjectPool; DeferredSpawn->FinishSpawning(SpawnTransform);}
	} else if (DeferredSpawn==nullptr && ObjectPool->NeverFailDeferredSpawn) {
		DeferredSpawn = ObjectPool->GetSpawnedObject();
		if (DeferredSpawn!=nullptr) {DeferredSpawn->ReturnToPool();}
	} ObjectPool->FlushObjectPool();
	//
	if (DeferredSpawn!=nullptr) {
		const APawn* Instigator = Cast<APawn>(WorldContextObject);
		if (Instigator==nullptr) { if (const AActor* ContextActor = Cast<AActor>(WorldContextObject)) {Instigator=ContextActor->GetInstigator();} }
		if (Instigator!=nullptr) {DeferredSpawn->SetInstigator(const_cast<APawn*>(Instigator));}
		if (Owner==nullptr) {DeferredSpawn->SetOwner(ObjectPool->GetOwner());}
		//
		DeferredSpawn->OwningPool = ObjectPool;
		DeferredSpawn->SharedPool = nullptr;
		DeferredSpawn->Initialize();
		//
		DeferredSpawn->SpawnFromPool(Reconstruct,SpawnOptions,SpawnTransform);
		SpawnSuccessful = DeferredSpawn->Spawned;
	} else {
		SpawnSuccessful = false;
		DeferredSpawn = ObjectPool->GetSpawnedObject();
	} return DeferredSpawn;
}

APooledActor* UObjectPool::FinishDeferredSpawnFromPool(APooledActor* Actor, const bool Reconstruct, const FTransform &SpawnTransform) {
	if (Actor->IsValidLowLevelFast()&&(!Actor->IsPendingKill())&&(!Actor->IsActorInitialized())) {
		Actor->FinishSpawning(SpawnTransform);
	} if (Actor->IsValidLowLevelFast()&&(!Actor->IsPendingKill())) {
		Actor->FinishSpawnFromPool(Reconstruct,SpawnTransform);
	} return Actor;
}

void UObjectPool::ReturnActor(APooledActor* PooledActor) {
	if (!GetOwner()->IsValidLowLevelFast()||this->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	if (!PooledActor->IsValidLowLevelFast()||PooledActor->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	//
	if (TemplateClass.Get()==nullptr) {return;}
	if (PooledActor->GetClass()->IsChildOf(TemplateClass->GetDefaultObject()->GetClass())) {
		if (!Pool.Contains(PooledActor)) {
			PooledActor->SetActorLocation(GetOwner()->GetActorLocation());
			Pool.Add(PooledActor);
		}///
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UObjectPool::GetObjectsFromPool(TArray<APooledActor*> &Spawned, TArray<APooledActor*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);} else {Inactive.Add(OBJ);}}
}

void UObjectPool::GetSpawnedObjects(TArray<APooledActor*> &Spawned) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);}}
}

void UObjectPool::GetInactiveObjects(TArray<APooledActor*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (!OBJ->Spawned) {Inactive.Add(OBJ);}}
}

APooledActor* UObjectPool::GetSpawnedObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

APooledActor* UObjectPool::GetInactiveObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (!Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pawn Pool Component Functions

UPawnPool::UPawnPool(const FObjectInitializer &OBJ) : Super(OBJ) {
	TemplateClass = APooledPawn::StaticClass();
	SetComponentTickEnabled(false);
	SetActive(true,false);
	//
	bWantsInitializeComponent = true;
	NeverFailDeferredSpawn = false;
	KeepOrphanActorsAlive = false;
	ReinitializeInstances = true;
	InstantiateOnDemand = false;
	AutoInitialize = true;
}

void UPawnPool::BeginPlay() {
	Super::BeginPlay();
	//
	if (AutoInitialize) {InitializeObjectPool();}
}

void UPawnPool::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (!KeepOrphanActorsAlive) {EmptyObjectPool();}
	else {
		for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
			if (Pool[ID]->Spawned) {continue;}
			Pool[ID]->Destroy(true,true);
		}///
	}///
	//
	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UPawnPool::InitializeObjectPool() {
	if (TemplateClass==nullptr) {
		LOG_OBJ(true,5.f,FColor::Red,GetNameSafe(this)+FString(" : ")+FString("Invalid Template Class!"));
	return;} EmptyObjectPool();
	//
	FTransform SpawnTransform(FRotator::ZeroRotator,FVector::ZeroVector,FVector(1.f,1.f,1.f));
	for (int32 I=0; I<PoolSize; I++) {
		const auto &ACT = GetWorld()->SpawnActorDeferred<APooledPawn>(TemplateClass,SpawnTransform,this->GetOwner(),GetOwner()->GetInstigator(),ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (ACT) {
			ACT->OwningPool = const_cast<UPawnPool*>(this);
			ACT->FinishSpawning(SpawnTransform);
	ACT->Initialize();}}
}

void UPawnPool::InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledPawn> Template, const int32 SizeOfPool) {
	TemplateClass = Template;
	PoolSize = SizeOfPool;
	//
	InitializeObjectPool();
}

void UPawnPool::FlushObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {Pool.RemoveAt(ID,1,false);}
	}///
}

void UPawnPool::EmptyObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (Pool[ID]->IsValidLowLevelFast()) {Pool[ID]->Destroy(true,true);}
	} Pool.Empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledPawn* UPawnPool::BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UPawnPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful) {
	if (!ObjectPool->IsValidLowLevelFast()||ObjectPool->IsPendingKill()||ObjectPool->GetOwner()==nullptr||PooledClass==nullptr) {return nullptr;}
	//
	if (ObjectPool->TemplateClass.Get() != PooledClass) {
		LOG_OBJ(true,5.f,FColor::Red,ObjectPool->GetName()+FString(" : ")+FString::Printf(TEXT("Requested Class(%s) not implemented by this Pool. Check the value of 'Template Class' on the Pool Component."),*PooledClass->GetName()));
	return nullptr;}
	//
	if (ObjectPool->Pool.Num()==0) {ObjectPool->InitializeObjectPool();}
	APooledPawn* DeferredSpawn = ObjectPool->GetInactiveObject();
	//
	if ((DeferredSpawn==nullptr) && ObjectPool->InstantiateOnDemand) {
		DeferredSpawn = ObjectPool->GetWorld()->SpawnActorDeferred<APooledPawn>(ObjectPool->TemplateClass,SpawnTransform,Owner,ObjectPool->GetOwner()->GetInstigator(),CollisionHandlingOverride);
		if (DeferredSpawn) {DeferredSpawn->OwningPool = ObjectPool; DeferredSpawn->FinishSpawning(SpawnTransform);}
	} else if (DeferredSpawn==nullptr && ObjectPool->NeverFailDeferredSpawn) {
		DeferredSpawn = ObjectPool->GetSpawnedObject();
		if (DeferredSpawn!=nullptr) {DeferredSpawn->ReturnToPool();}
	} ObjectPool->FlushObjectPool();
	//
	if (DeferredSpawn!=nullptr) {
		const APawn* Instigator = Cast<APawn>(WorldContextObject);
		if (Instigator==nullptr) { if (const AActor* ContextActor = Cast<AActor>(WorldContextObject)) {Instigator=ContextActor->GetInstigator();} }
		if (Instigator!=nullptr) {DeferredSpawn->SetInstigator(const_cast<APawn*>(Instigator));}
		if (Owner==nullptr) {DeferredSpawn->SetOwner(ObjectPool->GetOwner());}
		//
		DeferredSpawn->OwningPool = ObjectPool;
		DeferredSpawn->Initialize();
		//
		DeferredSpawn->SpawnFromPool(Reconstruct,SpawnOptions,SpawnTransform);
		SpawnSuccessful = DeferredSpawn->Spawned;
	} else {
		SpawnSuccessful = false;
		DeferredSpawn = ObjectPool->GetSpawnedObject();
	} return DeferredSpawn;
}

APooledPawn* UPawnPool::FinishDeferredSpawnFromPool(APooledPawn* Pawn, const bool Reconstruct, const FTransform &SpawnTransform) {
	if (Pawn->IsValidLowLevelFast()&&(!Pawn->IsPendingKill())&&(!Pawn->IsActorInitialized())) {
		Pawn->FinishSpawning(SpawnTransform);
	} if (Pawn->IsValidLowLevelFast()&&(!Pawn->IsPendingKill())) {
		Pawn->FinishSpawnFromPool(Reconstruct,SpawnTransform);
	} return Pawn;
}

void UPawnPool::ReturnActor(APooledPawn* PooledActor) {
	if (!GetOwner()->IsValidLowLevelFast()||this->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	if (!PooledActor->IsValidLowLevelFast()||PooledActor->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	//
	if (TemplateClass.Get()==nullptr) {return;}
	if (PooledActor->GetClass()->IsChildOf(TemplateClass->GetDefaultObject()->GetClass())) {
		if (!Pool.Contains(PooledActor)) {
			PooledActor->SetActorLocation(GetOwner()->GetActorLocation());
			Pool.Add(PooledActor);
		}///
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UPawnPool::GetObjectsFromPool(TArray<APooledPawn*> &Spawned, TArray<APooledPawn*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);} else {Inactive.Add(OBJ);}}
}

void UPawnPool::GetSpawnedObjects(TArray<APooledPawn*> &Spawned) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);}}
}

void UPawnPool::GetInactiveObjects(TArray<APooledPawn*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (!OBJ->Spawned) {Inactive.Add(OBJ);}}
}

APooledPawn* UPawnPool::GetSpawnedObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

APooledPawn* UPawnPool::GetInactiveObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (!Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Character Pool Component Functions

UCharacterPool::UCharacterPool(const FObjectInitializer &OBJ) : Super(OBJ) {
	TemplateClass = APooledCharacter::StaticClass();
	SetComponentTickEnabled(false);
	SetActive(true,false);
	//
	bWantsInitializeComponent = true;
	NeverFailDeferredSpawn = false;
	KeepOrphanActorsAlive = false;
	ReinitializeInstances = true;
	InstantiateOnDemand = false;
	AutoInitialize = true;
}

void UCharacterPool::BeginPlay() {
	Super::BeginPlay();
	//
	if (AutoInitialize) {InitializeObjectPool();}
}

void UCharacterPool::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (!KeepOrphanActorsAlive) {EmptyObjectPool();}
	else {
		for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
			if (Pool[ID]->Spawned) {continue;}
			Pool[ID]->Destroy(true,true);
		}///
	}///
	//
	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UCharacterPool::InitializeObjectPool() {
	if (TemplateClass==nullptr) {
		LOG_OBJ(true,5.f,FColor::Red,GetNameSafe(this)+FString(" : ")+FString("Invalid Template Class!"));
	return;} EmptyObjectPool();
	//
	FTransform SpawnTransform(FRotator::ZeroRotator,FVector::ZeroVector,FVector(1.f,1.f,1.f));
	for (int32 I=0; I<PoolSize; I++) {
		const auto &ACT = GetWorld()->SpawnActorDeferred<APooledCharacter>(TemplateClass,SpawnTransform,this->GetOwner(),GetOwner()->GetInstigator(),ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (ACT) {
			ACT->OwningPool = const_cast<UCharacterPool*>(this);
			ACT->FinishSpawning(SpawnTransform);
	ACT->Initialize();}}
}

void UCharacterPool::InitializeObjectPoolWithNewTemplateClass(const TSubclassOf<APooledCharacter> Template, const int32 SizeOfPool) {
	TemplateClass = Template;
	PoolSize = SizeOfPool;
	//
	InitializeObjectPool();
}

void UCharacterPool::FlushObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {Pool.RemoveAt(ID,1,false);}
	}///
}

void UCharacterPool::EmptyObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (Pool[ID]->IsValidLowLevelFast()) {Pool[ID]->Destroy(true,true);}
	} Pool.Empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledCharacter* UCharacterPool::BeginDeferredSpawnFromPool(const UObject* WorldContextObject, UCharacterPool* ObjectPool, UClass* PooledClass, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful) {
	if (!ObjectPool->IsValidLowLevelFast()||ObjectPool->IsPendingKill()||ObjectPool->GetOwner()==nullptr||PooledClass==nullptr) {return nullptr;}
	//
	if (ObjectPool->TemplateClass.Get() != PooledClass) {
		LOG_OBJ(true,5.f,FColor::Red,ObjectPool->GetName()+FString(" : ")+FString::Printf(TEXT("Requested Class(%s) not implemented by this Pool. Check the value of 'Template Class' on the Pool Component."),*PooledClass->GetName()));
	return nullptr;}
	//
	if (ObjectPool->Pool.Num()==0) {ObjectPool->InitializeObjectPool();}
	APooledCharacter* DeferredSpawn = ObjectPool->GetInactiveObject();
	//
	if ((DeferredSpawn==nullptr) && ObjectPool->InstantiateOnDemand) {
		DeferredSpawn = ObjectPool->GetWorld()->SpawnActorDeferred<APooledCharacter>(ObjectPool->TemplateClass,SpawnTransform,Owner,ObjectPool->GetOwner()->GetInstigator(),CollisionHandlingOverride);
		if (DeferredSpawn) {DeferredSpawn->OwningPool = ObjectPool; DeferredSpawn->FinishSpawning(SpawnTransform);}
	} else if (DeferredSpawn==nullptr && ObjectPool->NeverFailDeferredSpawn) {
		DeferredSpawn = ObjectPool->GetSpawnedObject();
		if (DeferredSpawn!=nullptr) {DeferredSpawn->ReturnToPool();}
	} ObjectPool->FlushObjectPool();
	//
	if (DeferredSpawn!=nullptr) {
		const APawn* Instigator = Cast<APawn>(WorldContextObject);
		if (Instigator==nullptr) { if (const AActor* ContextActor = Cast<AActor>(WorldContextObject)) {Instigator=ContextActor->GetInstigator();} }
		if (Instigator!=nullptr) {DeferredSpawn->SetInstigator(const_cast<APawn*>(Instigator));}
		if (Owner==nullptr) {DeferredSpawn->SetOwner(ObjectPool->GetOwner());}
		//
		DeferredSpawn->OwningPool = ObjectPool;
		DeferredSpawn->Initialize();
		//
		DeferredSpawn->SpawnFromPool(Reconstruct,SpawnOptions,SpawnTransform);
		SpawnSuccessful = DeferredSpawn->Spawned;
	} else {
		SpawnSuccessful = false;
		DeferredSpawn = ObjectPool->GetSpawnedObject();
	} return DeferredSpawn;
}

APooledCharacter* UCharacterPool::FinishDeferredSpawnFromPool(APooledCharacter* Character, const bool Reconstruct, const FTransform &SpawnTransform) {
	if (Character->IsValidLowLevelFast()&&(!Character->IsPendingKill())&&(!Character->IsActorInitialized())) {
		Character->FinishSpawning(SpawnTransform);
	} if (Character->IsValidLowLevelFast()&&(!Character->IsPendingKill())) {
		Character->FinishSpawnFromPool(Reconstruct,SpawnTransform);
	} return Character;
}

void UCharacterPool::ReturnActor(APooledCharacter* PooledActor) {
	if (!GetOwner()->IsValidLowLevelFast()||this->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	if (!PooledActor->IsValidLowLevelFast()||PooledActor->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	//
	if (TemplateClass.Get()==nullptr) {return;}
	if (PooledActor->GetClass()->IsChildOf(TemplateClass->GetDefaultObject()->GetClass())) {
		if (!Pool.Contains(PooledActor)) {
			PooledActor->SetActorLocation(GetOwner()->GetActorLocation());
			Pool.Add(PooledActor);
		}///
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UCharacterPool::GetObjectsFromPool(TArray<APooledCharacter*> &Spawned, TArray<APooledCharacter*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);} else {Inactive.Add(OBJ);}}
}

void UCharacterPool::GetSpawnedObjects(TArray<APooledCharacter*> &Spawned) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (OBJ->Spawned) {Spawned.Add(OBJ);}}
}

void UCharacterPool::GetInactiveObjects(TArray<APooledCharacter*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
	if (!OBJ->Spawned) {Inactive.Add(OBJ);}}
}

APooledCharacter* UCharacterPool::GetSpawnedObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

APooledCharacter* UCharacterPool::GetInactiveObject() const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
	if (!Pool[ID]->Spawned) {return Pool[ID];}}
	//
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Shared Object Pool Component Functions

USharedObjectPool::USharedObjectPool(const FObjectInitializer &OBJ) : Super(OBJ) {
	SetComponentTickEnabled(false);
	SetActive(true,false);
	//
	bWantsInitializeComponent = true;
	NeverFailDeferredSpawn = false;
	KeepOrphanActorsAlive = false;
	ReinitializeInstances = true;
	InstantiateOnDemand = false;
	AutoInitialize = true;
}

void USharedObjectPool::PostInitProperties() {
	Super::PostInitProperties();
}

void USharedObjectPool::BeginPlay() {
	Super::BeginPlay();
	//
	if (AutoInitialize) {InitializeObjectPool();}
}

void USharedObjectPool::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (!KeepOrphanActorsAlive) {
		EmptyObjectPool(APooledActor::StaticClass());
	} else {
		for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
			if (Pool[ID]->Spawned) {continue;}
			Pool[ID]->Destroy(true,true);
		}///
	}///
	//
	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void USharedObjectPool::InitializeObjectPool() {
	if (TemplateClasses.Num()<=0) {
		LOG_OBJ(true,5.f,FColor::Red,GetNameSafe(this)+FString(" : ")+FString("Invalid Template Classes!"));
	return;} EmptyObjectPool(APooledActor::StaticClass());
	//
	FTransform SpawnTransform(FRotator::ZeroRotator,FVector::ZeroVector,FVector(1.f,1.f,1.f));
	TArray<TSubclassOf<APooledActor>>Classes;
	TemplateClasses.GenerateKeyArray(Classes);
	//
	for (const TSubclassOf<APooledActor>Class : Classes) {
		if (Class.Get()==nullptr) {continue;}
		int32 PoolSize = TemplateClasses.FindRef(Class);
		//
		for (int32 I=0; I<PoolSize; I++) {
			const auto &ACT = GetWorld()->SpawnActorDeferred<APooledActor>(Class,SpawnTransform,this->GetOwner(),GetOwner()->GetInstigator(),ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
			if (ACT) {
				ACT->OwningPool = nullptr;
				ACT->SharedPool = const_cast<USharedObjectPool*>(this);
				ACT->FinishSpawning(SpawnTransform);
		ACT->Initialize();}}
	}///
	//
	FlushObjectPool();
}

void USharedObjectPool::FlushObjectPool() {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {Pool.RemoveAt(ID,1,false);}
	}///
}

void USharedObjectPool::EmptyObjectPool(const UClass* Class) {
	if (!Pool.IsValidIndex(0)) {return;}
	//
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsA(Class)) {continue;}
		if (Pool[ID]->IsValidLowLevelFast()) {Pool[ID]->Destroy(true,true);}
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void USharedObjectPool::GetObjectsFromPool(const UClass* Class, TArray<APooledActor*> &Spawned, TArray<APooledActor*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
		if (!OBJ->IsA(Class)) {continue;}
		//
		if (OBJ->Spawned) {Spawned.Add(OBJ);} else {Inactive.Add(OBJ);}
	}///
}

void USharedObjectPool::GetSpawnedObjects(const UClass* Class, TArray<APooledActor*> &Spawned) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
		if (!OBJ->IsA(Class)) {continue;}
		//
		if (OBJ->Spawned) {Spawned.Add(OBJ);}
	}///
}

void USharedObjectPool::GetInactiveObjects(const UClass* Class, TArray<APooledActor*> &Inactive) {
	for (const auto &OBJ : Pool) {
		if (!OBJ->IsValidLowLevelFast()||OBJ->IsPendingKill()) {continue;}
		if (!OBJ->IsA(Class)) {continue;}
		//
		if (!OBJ->Spawned) {Inactive.Add(OBJ);}
	}///
}

APooledActor* USharedObjectPool::GetSpawnedObject(const UClass* Class) const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
		if (!Pool[ID]->IsA(Class)) {continue;}
		//
		if (Pool[ID]->Spawned) {return Pool[ID];}
	}///
	//
	return nullptr;
}

APooledActor* USharedObjectPool::GetInactiveObject(const UClass* Class) const {
	for (int32 ID = Pool.Num()-1; ID>=0; --ID) {
		if (!Pool[ID]->IsValidLowLevelFast()||Pool[ID]->IsPendingKill()) {continue;}
		if (!Pool[ID]->IsA(Class)) {continue;}
		//
		if (!Pool[ID]->Spawned) {return Pool[ID];}
	}///
	//
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

APooledActor* USharedObjectPool::BeginDeferredSpawnFromPool(const UObject* WorldContextObject, USharedObjectPool* SharedPool, UClass* Class, const FPoolSpawnOptions &SpawnOptions, const FTransform &SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, AActor* Owner, const bool Reconstruct, bool &SpawnSuccessful) {
	if (!SharedPool->IsValidLowLevelFast()||SharedPool->IsPendingKill()||SharedPool->GetOwner()==nullptr) {
		UE_LOG(LogTemp,Warning,TEXT("{Pool}:: %s"),TEXT("Target Shared-Pool is about to be destroyed. Spawn aborted!"));	
	return nullptr;}
	//
	//
	if (Class==nullptr) {
		UE_LOG(LogTemp,Warning,TEXT("{Begin Deferred Spawn from Pool}: Invalid Class."));
	return nullptr;}
	//
	bool IsTemplate = false;
	TArray<TSubclassOf<APooledActor>>Classes;
	SharedPool->TemplateClasses.GenerateKeyArray(Classes);
	//
	for (const TSubclassOf<APooledActor>TemplateClass : Classes) {
		if (Class==nullptr) {break;}
		if (TemplateClass.Get()==nullptr) {continue;}
		if (!Class->GetName().Equals(TemplateClass.Get()->GetName())) {continue;}
		//
		IsTemplate = true;
		if (SharedPool->TemplateClasses.FindChecked(TemplateClass)<=0) {
			UE_LOG(LogTemp,Warning,TEXT("{%s}:: %s (%s)"),*SharedPool->GetName(),TEXT("Target Class is zero-sized in Target Shared-Pool!"),*Class->GetName());
		break;}
	} if (!IsTemplate) {
		UE_LOG(LogTemp,Warning,TEXT("{%s}:: %s (%s)"),*SharedPool->GetName(),TEXT("This Shared-Pool does NOT implement Target Template Class. Spawn Aborted:"),*Class->GetName());
	return nullptr;}
	//
	//
	if (SharedPool->Pool.Num()==0) {SharedPool->InitializeObjectPool();}
	APooledActor* DeferredSpawn = SharedPool->GetInactiveObject(Class);
	//
	if ((DeferredSpawn==nullptr) && SharedPool->InstantiateOnDemand) {
		DeferredSpawn = SharedPool->GetWorld()->SpawnActorDeferred<APooledActor>(Class,SpawnTransform,Owner,SharedPool->GetOwner()->GetInstigator(),CollisionHandlingOverride);
		if (DeferredSpawn) {DeferredSpawn->SharedPool = SharedPool; DeferredSpawn->OwningPool = nullptr; DeferredSpawn->FinishSpawning(SpawnTransform);}
	} else if (DeferredSpawn==nullptr && SharedPool->NeverFailDeferredSpawn) {
		DeferredSpawn = SharedPool->GetSpawnedObject(Class);
		if (DeferredSpawn!=nullptr) {DeferredSpawn->ReturnToPool();}
	} SharedPool->FlushObjectPool();
	//
	if (DeferredSpawn!=nullptr) {
		const APawn* Instigator = Cast<APawn>(WorldContextObject);
		if (Instigator==nullptr) { if (const AActor* ContextActor = Cast<AActor>(WorldContextObject)) {Instigator = ContextActor->GetInstigator();} }
		if (Instigator!=nullptr) {DeferredSpawn->SetInstigator(const_cast<APawn*>(Instigator));}
		if (Owner==nullptr) {DeferredSpawn->SetOwner(SharedPool->GetOwner());}
		//
		DeferredSpawn->SharedPool = SharedPool;
		DeferredSpawn->OwningPool = nullptr;
		DeferredSpawn->Initialize();
		//
		DeferredSpawn->SpawnFromPool(Reconstruct,SpawnOptions,SpawnTransform);
		SpawnSuccessful = DeferredSpawn->Spawned;
	} else {
		SpawnSuccessful = false;
		DeferredSpawn = SharedPool->GetSpawnedObject(Class);
	}///
	//
	return DeferredSpawn;
}

APooledActor* USharedObjectPool::FinishDeferredSpawnFromPool(APooledActor* Actor, const bool Reconstruct, const FTransform &SpawnTransform) {
	if (Actor->IsValidLowLevelFast()&&(!Actor->IsPendingKill())&&(!Actor->IsActorInitialized())) {
		Actor->FinishSpawning(SpawnTransform);
	} if (Actor->IsValidLowLevelFast()&&(!Actor->IsPendingKill())) {
		Actor->FinishSpawnFromPool(Reconstruct,SpawnTransform);
	} return Actor;
}

void USharedObjectPool::ReturnActor(APooledActor* PooledActor) {
	if (!GetOwner()->IsValidLowLevelFast()||this->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	if (!PooledActor->IsValidLowLevelFast()||PooledActor->IsPendingKill()) {PooledActor->Destroy(true,true); return;}
	//
	TArray<TSubclassOf<APooledActor>>Classes;
	TemplateClasses.GenerateKeyArray(Classes);
	//
	for (const TSubclassOf<APooledActor>Class : Classes) {
		if (Class.Get()==nullptr) {continue;}
		//
		if (PooledActor->GetClass()->IsChildOf(Class->GetDefaultObject()->GetClass())) {
			if (!Pool.Contains(PooledActor)) {
				PooledActor->SetActorLocation(GetOwner()->GetActorLocation());
				Pool.Add(PooledActor);
			}///
		}///
	}///
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LOG_OBJ(const bool Debug,const float Duration, const FColor Color, const FString Message) {
	if (!Debug) return; UE_LOG(LogTemp,Warning,TEXT("{Pool}:: %s"),*Message); if (!GEngine) {return;}
	GEngine->AddOnScreenDebugMessage(-1,Duration,Color,FString::Printf(TEXT("{Pool}:: %s"),*Message));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////