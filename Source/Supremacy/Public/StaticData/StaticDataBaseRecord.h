#pragma once

#include "StaticDataBaseRecord.generated.h"

USTRUCT(BlueprintType)
struct FStaticDataBaseRecord
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FGuid id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FString label;
};