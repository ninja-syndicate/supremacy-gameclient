#pragma once

#include "Base.h"
#include "CoreMinimal.h"

class UStaticData;

namespace StaticDataImporter
{
	class MechSkinCompatibility : public Base
	{
	public:
		MechSkinCompatibility();
		virtual ~MechSkinCompatibility() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
