#include "Weapons/WeaponBarrel.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void UWeaponBarrel::ShotFiredMulticast_Implementation() {
	ShotFired.Broadcast();
}


void UWeaponBarrel::Shoot(const bool Trigger) {
	if (ClientSideAim && GetOwner()->GetRemoteRole() == ROLE_Authority && Trigger) {
		Aim = GetComponentTransform().GetUnitAxis(EAxis::X);
		Location = GetComponentTransform().GetLocation();
		ShootRepCSA(Trigger, UGameplayStatics::RebaseLocalOriginOntoZero(GetWorld(), Location), Aim);
	}
	else {
		ShootRep(Trigger);
	}
}

void UWeaponBarrel::ShootRep_Implementation(const bool Trigger) {
	Shooting = Trigger;
}

bool UWeaponBarrel::ShootRep_Validate(const bool Trigger) {
	return true;
}

void UWeaponBarrel::ShootRepCSA_Implementation(const bool Trigger, const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim) {
	Location = UGameplayStatics::RebaseZeroOriginOntoLocal(GetWorld(), NewLocation);
	Aim = NewAim;
	RemoteAimReceived = true;

	Shooting = Trigger;
}

bool UWeaponBarrel::ShootRepCSA_Validate(const bool Trigger, const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim) {
	return true;
}

void UWeaponBarrel::ClientAim_Implementation(const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim) {
	Location = UGameplayStatics::RebaseZeroOriginOntoLocal(GetWorld(),NewLocation);
	Aim = NewAim;
	RemoteAimReceived = true;
}
bool UWeaponBarrel::ClientAim_Validate(const FVector_NetQuantize NewLocation, const FVector_NetQuantizeNormal NewAim) {
	return true;
}

void UWeaponBarrel::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponBarrel, BulletClass);
	DOREPLIFETIME(UWeaponBarrel, Shooting);
	DOREPLIFETIME(UWeaponBarrel, ShootingBlocked);
}