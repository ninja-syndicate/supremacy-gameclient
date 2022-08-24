#pragma once

#include "CoreMinimal.h"
#include "UserAction.generated.h"

USTRUCT(BlueprintType)
struct FUserAction
{
	GENERATED_BODY()

public:
	/**
	 * The ability ID associated with this user action.
	 *
	 * @note For now, this is stored as an integer as we have enum in blueprint.
	 * We probably should make a C++ AbilityID enum and switch to it eventually.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AbilityId;

	/** The 2D target location of the user action. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Location;

	/** The user action event ID. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EventId;

	/** The username of who triggered this user action. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TriggeredByUsername;

	/** War machine hash. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WarMachineHash;

	FUserAction()
	{
		AbilityId = 0;
		Location = FVector2D();
	}

	FUserAction(const int AbilityId, const FVector2D Location)
		: AbilityId(AbilityId), Location(Location)
	{}
};