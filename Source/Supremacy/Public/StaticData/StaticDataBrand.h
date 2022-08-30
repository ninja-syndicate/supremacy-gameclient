#pragma once

#include "StaticDataBaseRecord.h"
#include "StaticDataFaction.h"
#include "StaticDataBrand.generated.h"

namespace StaticDataImporter
{
	class Brand;
}

UCLASS(BlueprintType)
class UStaticDataBrand  : public UStaticDataBaseRecord
{
	friend class StaticDataImporter::Brand;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="References", meta=(AllowPrivateAccess=true))
	UStaticDataFaction *Faction;
};
