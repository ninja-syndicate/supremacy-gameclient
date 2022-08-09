#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

USTRUCT(BlueprintType)
struct FFaction {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="id"))
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="name"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="color"))
	FColor Color;

	FFaction(): Color(FColor(255, 255, 255, 255)) {}
};
