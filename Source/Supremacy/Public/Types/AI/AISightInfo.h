#pragma once

#include "CoreMinimal.h"
#include "AIWarMachineInfo.h"
#include "AISightInfo.generated.h"

/**
 * 
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAISightInfo {
	GENERATED_BODY()

public:
	UPROPERTY(Category = "AI Sight Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIWarMachineInfo> WarMachines;

	FAISightInfo() {}
};
