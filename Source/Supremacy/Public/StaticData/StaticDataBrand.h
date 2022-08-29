#pragma once

#include "StaticDataBaseRecord.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.generated.h"

UCLASS(BlueprintType)
class UStaticDataBrand  : public UStaticDataBaseRecord
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataFaction *Faction;
};
