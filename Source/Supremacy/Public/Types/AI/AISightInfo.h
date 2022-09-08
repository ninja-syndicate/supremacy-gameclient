#pragma once

#include "CoreMinimal.h"
#include "AIWarMachineInfo.h"
#include "AISightInfo.generated.h"

USTRUCT(BlueprintType)
struct FAISightInfo {
	GENERATED_BODY()

public:
	UPROPERTY(Category = "AI Sight Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIWarMachineInfo> warMachines;

	FAISightInfo() {}
};
