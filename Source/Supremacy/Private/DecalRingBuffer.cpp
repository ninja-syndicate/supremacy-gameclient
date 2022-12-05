// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalRingBuffer.h"

// the variable 'DecalBuffers', according to visual studio, is getting optimised out in the 
// middle of this function, after the for loop line, leading to uninitialised values, but 
// after adding these #pragmas, the problem goes away. not sure what is going on here.
#pragma optimize( "", off )
void UDecalRingBuffer::BeginPlay() {
	Super::BeginPlay();

	TArray<FString> Keys;
	DecalBuffers.GetKeys(Keys);

	UWorld* World = GetWorld();

	for(int keyIndex = 0; keyIndex < Keys.Num(); keyIndex++) {
		FString Key = Keys[keyIndex];
		FPooledDecalType *DecalType = DecalBuffers.Find(Key);
		DecalType->Buffer.Reserve(DecalType->Capacity);

		for (int32 i = 0; i < DecalType->Capacity; i++) {
			APooledDecalActor* DecalActor = World->SpawnActor<APooledDecalActor>();
			DecalActor->SetHidden(true);
			DecalType->Buffer.Emplace(DecalActor);
		}
	}
}
#pragma optimize( "", on )

ADecalActor* UDecalRingBuffer::AllocateDecal(FString DecalType, float LifeTime, UMaterialInstanceDynamic *Material) {
	FPooledDecalType* DecalBuffer = DecalBuffers.Find(DecalType);
	if (!DecalBuffer) return 0;

	UWorld* World = GetWorld();

	APooledDecalActor* Actor = DecalBuffer->Buffer[DecalBuffer->CurrentIndex];
	DecalBuffer->CurrentIndex += 1;
	if (DecalBuffer->CurrentIndex >= DecalBuffer->Buffer.Num()) DecalBuffer->CurrentIndex = 0;

	Actor->SetMaterial(Material, LifeTime, World->GetTimeSeconds());

	return Actor;
}