#pragma once

#include "CoreMinimal.h"
#include "AICachedScriptResponse.generated.h"

/**
 * Every information that can be retrieved from the script-side on AI tick goes here.
 * These are cached to allow scripts to run in background threads and to ensure the result does not change due to relative timing of execution order.
 */
USTRUCT(BlueprintType)
struct FAICachedScriptResponse {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, TObjectPtr<AActor>> Sight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> AvailableActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInsideBattleZone = false;

	//UPROPERTY(EditAnywhere, BluerpintReadWrite)
	//int MovementResult = EPathFollowingResult::Invalid;

	FAICachedScriptResponse() {}
};
