#pragma once

#include "StaticDataBaseRecord.generated.h"

USTRUCT(BlueprintType)
struct FStaticDataBaseRecord
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGuid ID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString Label;
};