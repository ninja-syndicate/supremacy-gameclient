#include "Core/Game/SupremacyPlayerState.h"
#include "Net/UnrealNetwork.h"

ASupremacyPlayerState::ASupremacyPlayerState()
{
	// Set default UserID for testing
	UserID = "unauthorised-" + FGuid::NewGuid().ToString();
}

void ASupremacyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASupremacyPlayerState, UserID);
	DOREPLIFETIME(ASupremacyPlayerState, Faction);
}

void ASupremacyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	// Remember these details in between maps
	ASupremacyPlayerState* PS = Cast<ASupremacyPlayerState>(PlayerState);
	if (!ensure(PS)) return;
	PS->UserID = UserID;
	PS->Faction = Faction;
}

void ASupremacyPlayerState::SetUser(const FUser& User)
{
	SetPlayerName(User.Username);
	UserID = User.ID;
	Faction = FFaction(User.Faction);
}

FString ASupremacyPlayerState::GetTeamID_Implementation()
{
	return Faction.ID;
}
