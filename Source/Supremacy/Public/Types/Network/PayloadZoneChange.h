#pragma once

#include "PayloadZoneChange.generated.h"

USTRUCT(BlueprintType)
struct FPayloadZoneChange {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Zone_Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Warn_Time;

	FPayloadZoneChange() : Zone_Index(0), Warn_Time(0) {}
};
