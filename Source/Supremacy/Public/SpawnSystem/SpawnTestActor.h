// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnTestActor.generated.h"

UCLASS()
class SUPREMACY_API ASpawnTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Initialize(float InRadius);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Sphere collision component for the spawn test actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta=(AllowPrivateAccess = "true"))
	class USphereComponent* CollisionComponent;

	/** Sphere collision component radius */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta=(AllowPrivateAccess = "true"))
	float Radius;
};
