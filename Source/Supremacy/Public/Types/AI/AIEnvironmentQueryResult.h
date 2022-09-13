#pragma once

#include "CoreMinimal.h"
#include "AIEnvironmentQueryResult.generated.h"

UENUM(BlueprintType)
enum class EEnvironmentQueryStatus : uint8
{
	EnvQueryStatus_Ready = 0 UMETA(DisplayName = "Ready"),
	EnvQueryStatus_Processing UMETA(DisplayName = "Processing"),
	EnvQueryStatus_Success UMETA(DisplayName = "Success"),
	EnvQueryStatus_Failed UMETA(DisplayName = "Failed")
};

/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIEnvironmentQueryResult {
	GENERATED_BODY()

public:
	/** The status of the environment query. Note that the type needs to be integer for proper JSON parsing. */
	UPROPERTY(Category = "AI Environment Query Status", EditAnywhere, BlueprintReadWrite)
	int Status = 0;
	
	/** The resulting location of the environment query. Only valid if complete. */
	UPROPERTY(Category = "AI Environment Query Status", EditAnywhere, BlueprintReadWrite)
	FVector3f Location = FVector3f::ZeroVector;

	FAIEnvironmentQueryResult() {}
};
