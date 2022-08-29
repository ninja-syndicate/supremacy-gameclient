#pragma once

#include "Base.h"
#include "CoreMinimal.h"


namespace StaticDataImporter
{
	class Brand : public Base
	{
	public:
		Brand();
		virtual ~Brand() = default;
	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}