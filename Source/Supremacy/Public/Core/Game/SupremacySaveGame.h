#pragma once

#include "GameFramework/SaveGame.h"
#include "SupremacySaveGame.generated.h"

UCLASS()
class SUPREMACY_API USupremacySaveGame final : public USaveGame
{
	GENERATED_BODY()

	public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString Token;
};
