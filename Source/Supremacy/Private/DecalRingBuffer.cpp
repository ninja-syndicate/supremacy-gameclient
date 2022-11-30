// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalRingBuffer.h"

void UDecalRingBuffer::BeginPlay() {
	TArray<FString> Keys;
	DecalBuffers.GetKeys(Keys);

	UWorld* World = GetWorld();

	for (auto &Key : Keys) {
		FPooledDecalType *DecalType = DecalBuffers.Find(Key);
		DecalType->Buffer.Reserve(DecalType->Capacity);

		for (int32 i = 0; i < DecalType->Capacity; i++) {
			APooledDecalActor* DecalActor = World->SpawnActor<APooledDecalActor>();
			DecalActor->SetHidden(true);
			DecalType->Buffer.Emplace(DecalActor);
		}
	}
}

ADecalActor* UDecalRingBuffer::AllocateDecal(FString DecalType, float LifeTime, UMaterialInstanceDynamic *Material) {
	FPooledDecalType* DecalBuffer = DecalBuffers.Find(DecalType);
	if (!DecalBuffer) return 0;

	UWorld* World = GetWorld();

	APooledDecalActor* Actor = DecalBuffer->Buffer[DecalBuffer->CurrentIndex];
	DecalBuffer->CurrentIndex += 1;

	Actor->SetMaterial(Material, LifeTime, World->GetTimeSeconds());

	return Actor;
}