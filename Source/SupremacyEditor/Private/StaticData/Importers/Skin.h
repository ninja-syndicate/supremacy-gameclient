#pragma once

#include "Base.h"
#include "CoreMinimal.h"

class UStaticData;

namespace StaticDataImporter
{
	class Skin : public Base
	{
	public:
		Skin();
		virtual ~Skin() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
