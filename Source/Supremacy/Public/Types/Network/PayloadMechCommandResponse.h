#pragma once

#include "CoreMinimal.h"
#include "PayloadMechCommandResponse.generated.h"

USTRUCT(BlueprintType)
struct FPayloadMechCommandResponse {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Event_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString War_Machine_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Is_Valid;

	FPayloadMechCommandResponse() : Is_Valid(false) {}
};