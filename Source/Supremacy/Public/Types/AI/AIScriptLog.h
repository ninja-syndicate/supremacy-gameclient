#pragma once

#include "CoreMinimal.h"
#include "AIScriptLog.generated.h"

/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIScriptLog {
	GENERATED_BODY()

public:
	UPROPERTY(Category = "AI Script Log", EditAnywhere, BlueprintReadWrite)
	FString Command;

	UPROPERTY(Category = "AI Script Log", EditAnywhere, BlueprintReadWrite)
	FString Severity;

	UPROPERTY(Category = "AI Script Log", EditAnywhere, BlueprintReadWrite)
	FString Message;

	FAIScriptLog() {}
};
