#pragma once

#include "Base.h"
#include "CoreMinimal.h"

class UStaticData;

namespace StaticDataImporter
{
	class Weapon : public Base
	{
	public:
		Weapon();
		virtual ~Weapon() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}