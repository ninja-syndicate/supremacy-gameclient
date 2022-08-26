#pragma once

#include "Base.h"
#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class Faction : public Base
	{
	public:
		Faction();
		virtual ~Faction() = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
