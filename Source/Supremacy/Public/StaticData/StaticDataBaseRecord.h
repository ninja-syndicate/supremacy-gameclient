#pragma once

#include "StaticDataBaseRecord.generated.h"

UCLASS(BlueprintType)
class UStaticDataBaseRecord : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ID", meta=(AllowPrivateAccess=true))
	FGuid ID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields",  meta=(AllowPrivateAccess=true))
	FString Label;
};