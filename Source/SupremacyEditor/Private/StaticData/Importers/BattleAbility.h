#pragma once

#include "Base.h"
#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class BattleAbility : public Base
	{
	public:
		BattleAbility();
		virtual ~BattleAbility() override = default;
	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}