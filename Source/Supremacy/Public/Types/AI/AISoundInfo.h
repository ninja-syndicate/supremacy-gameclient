#pragma once

#include "CoreMinimal.h"
#include "AISoundInfo.generated.h"

USTRUCT(BlueprintType)
struct FAISoundInfo {
	GENERATED_BODY()

public:
	/** The location of the sound. */
	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	FVector3f location = FVector3f::ZeroVector;

	/** The type of the sound. */
	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	FString type;

	UPROPERTY(Category = "AI Sound Info", EditAnywhere, BlueprintReadWrite)
	bool isFriendly = false;

	FAISoundInfo() {}
};
