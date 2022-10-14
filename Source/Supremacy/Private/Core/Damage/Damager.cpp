// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Damage/Damager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDamager::UDamager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamager::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UDamager::Initialize_Implementation()
{
	const auto Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDamager: Invalid actor component owner!"));
		return;
	}
	Instigator = Owner->GetInstigator();
	Controller = Owner->GetInstigatorController();
}

// Called every frame
void UDamager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// NOTE: BaseDamage is technically not necessary, but since it's currently stored in blueprint, no easy way to access.
float UDamager::ApplyDamage_Implementation(AActor* DamagedActor, float BaseDamage, TSubclassOf<UDamageType> DamageTypeClass)
{
	// Re-intialize in case of object pooling.
	Initialize();

	const float ActualDamage = UGameplayStatics::ApplyDamage(DamagedActor, BaseDamage, Controller, GetOwner(), DamageTypeClass);
	return ActualDamage;
}
