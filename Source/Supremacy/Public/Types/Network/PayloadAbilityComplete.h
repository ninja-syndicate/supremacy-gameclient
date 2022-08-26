#pragma once

#include "PayloadAbilityComplete.generated.h"

USTRUCT(BlueprintType)
struct FPayloadAbilityComplete {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Event_ID;
};
