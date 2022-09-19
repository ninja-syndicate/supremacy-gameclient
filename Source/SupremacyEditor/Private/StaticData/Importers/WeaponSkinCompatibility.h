#pragma once

#include "Base.h"
#include "CoreMinimal.h"

class UStaticData;

namespace StaticDataImporter
{
	class WeaponSkinCompatibility : public Base
	{
	public:
		WeaponSkinCompatibility();
		virtual ~WeaponSkinCompatibility() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
