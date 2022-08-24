#include "Utilities/Utility.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AUtility::AUtility() {}

void AUtility::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 
	DOREPLIFETIME( AUtility, GameplayTagContainer );
}

