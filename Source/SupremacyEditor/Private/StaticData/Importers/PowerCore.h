#pragma once

#include "Base.h"
#include "CoreMinimal.h"

class UStaticData;

namespace StaticDataImporter
{
	class PowerCore : public Base
	{
	public:
		PowerCore();
		virtual ~PowerCore() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
