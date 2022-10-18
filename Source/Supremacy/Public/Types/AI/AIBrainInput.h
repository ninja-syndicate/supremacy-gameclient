#pragma once

#include "CoreMinimal.h"
#include "AIPerceptionInfo.h"
#include "AIScriptLog.h"
#include "AIWarMachineInfo.h"
#include "AIEnvironmentQueryResult.h"
#include "AIBrainInput.generated.h"

// TODO: Change name of the struct?
/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIBrainInput {
	GENERATED_BODY()

public:
	/** Information about itself. */
	UPROPERTY(Category = "AI Brain Input", EditAnywhere, BlueprintReadWrite)
	FAIWarMachineInfo Self;

	/** Elapsed time since last tick. */
	UPROPERTY(Category = "AI Brain Input", EditAnywhere, BlueprintReadWrite)
	float DeltaTime = 0;

	/** Currently perceived information. */
	UPROPERTY(Category = "AI Brain Input", EditAnywhere, BlueprintReadWrite)
	FAIPerceptionInfo Perception;

	/** Script logs. */
	UPROPERTY(Category = "AI Brain Input", EditAnywhere, BlueprintReadWrite)
	TArray<FAIScriptLog> Errors;

	/** Environment Query Results. */
	UPROPERTY(Category = "AI Brain Input", EditAnywhere, BlueprintReadWrite)
	TMap<FString, FAIEnvironmentQueryResult> EnvQueryStatus;

	FAIBrainInput() {}
};
