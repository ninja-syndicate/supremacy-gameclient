#pragma once

#include "StaticDataBaseRecord.generated.h"

USTRUCT(BlueprintType)
struct FStaticDataBaseRecord
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="id"))
	FGuid id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="id"))
	FString label;
};