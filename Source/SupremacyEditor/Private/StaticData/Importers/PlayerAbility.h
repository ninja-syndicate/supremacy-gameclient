#pragma once

#include "Base.h"
#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class PlayerAbility : public Base
	{
	public:
		PlayerAbility();
		virtual ~PlayerAbility() override = default;
	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}