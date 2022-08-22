#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserActionActor.generated.h"

UCLASS()
class SUPREMACY_API AUserActionActor final : public AActor
{
	GENERATED_BODY()

public:
	/** The user action event ID. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
	FString EventId;

	/** The username of who triggered this user action. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
	FString TriggeredByUsername;

	/** War machine hash. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
	FString WarMachineHash;
};