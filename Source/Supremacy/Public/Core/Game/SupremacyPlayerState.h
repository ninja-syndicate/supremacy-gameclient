#pragma once

#include "GameFramework/PlayerState.h"
#include "Types/Faction.h"
#include "Types/TeamMemberInterface.h"
#include "Types/Network/User.h"

#include "SupremacyPlayerState.generated.h"

UCLASS()
class SUPREMACY_API ASupremacyPlayerState final : public APlayerState, public ITeamMemberInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Replicated)
	FString UserID;
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	FFaction Faction;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CopyProperties(APlayerState* PlayerState) override;
	
	/**
	 * @brief Set UserID, Username and Faction from a FUser
	 * @param User FUser, generally returned from AuthSubsystem login.
	 */
	UFUNCTION(BlueprintCallable)
	void SetUser(const FUser& User);

	//~Begin ITeamMemberInterface
	virtual FString GetTeamID_Implementation() override;
	//~End ITeamMemberInterface
};
