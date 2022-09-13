#pragma once

#include "CoreMinimal.h"
#include "AIInteractableInfo.generated.h"

// NOTE: This struct may eventually be removed/significnalty modified.
USTRUCT(BlueprintType)
struct FAIInteractableInfo {
	GENERATED_BODY()

public:
	UPROPERTY(Category = "AI Interactable Info", EditAnywhere, BlueprintReadWrite)
	FString Tag;

	UPROPERTY(Category = "AI Interactable Info", EditAnywhere, BlueprintReadWrite)
	FString EventID;

	UPROPERTY(Category = "AI Interactable Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Location = FVector3f::ZeroVector;

	UPROPERTY(Category = "AI Interactable Info", EditAnywhere, BlueprintReadWrite)
	FString InstigatorFactionID;

	FAIInteractableInfo() {}
};
