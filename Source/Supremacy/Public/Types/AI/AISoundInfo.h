#pragma once

#include "CoreMinimal.h"
#include "AISoundInfo.generated.h"

/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAISoundInfo {
	GENERATED_BODY()

public:
	/** The location of the sound. */
	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Location = FVector3f::ZeroVector;

	/** The type of the sound. */
	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	FString Type;

	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	bool IsFriendly = false;

	FAISoundInfo() {}
};
