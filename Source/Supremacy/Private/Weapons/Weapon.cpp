// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 
	DOREPLIFETIME( AWeapon, GameplayTagContainer );
	DOREPLIFETIME( AWeapon, Struct );
	DOREPLIFETIME_CONDITION( AWeapon, TargetLocation, COND_InitialOnly );
}

void AWeapon::Trigger_Implementation()
{
	
}

void AWeapon::Release_Implementation()
{

}

bool AWeapon::IsTriggered() const
{
	return bIsTriggered;
}

bool AWeapon::CanFriendlyFire() const
{
	return bEnableFriendlyFire;
}

void AWeapon::SetFriendlyFire(bool Enable)
{
	bEnableFriendlyFire = Enable;
}