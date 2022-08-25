#include "Mechs/Mech.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMech::AMech() {}

void AMech::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 
	DOREPLIFETIME_CONDITION( AMech, WarMachineStruct, COND_InitialOnly );
}

void AMech::OnRep_SetWarMachineStruct()
{
	Setup();
}

