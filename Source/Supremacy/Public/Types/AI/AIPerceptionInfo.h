#pragma once

#include "CoreMinimal.h"
#include "AIWarMachineInfo.h"
#include "AIDamageInfo.h"
#include "AIInteractableInfo.h"
#include "AISightInfo.h"
#include "AISoundInfo.h"
#include "AIPerceptionInfo.generated.h"

/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIPerceptionInfo {
	GENERATED_BODY()

public:
	/** Sight information. TOOD: maybe change to aisightinfo */
	UPROPERTY(Category = "AI Perception Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIWarMachineInfo> Sight;

	/** Sound information. */
	UPROPERTY(Category = "AI Perception Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAISoundInfo> Sound;

	/** Damage information. */
	UPROPERTY(Category = "AI Perception Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIDamageInfo> Damage;

	UPROPERTY(Category = "AI Perception Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIInteractableInfo> Interactable;

	FAIPerceptionInfo() {}
};
