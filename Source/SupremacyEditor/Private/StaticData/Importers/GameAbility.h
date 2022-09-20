#pragma once

#include "Base.h"
#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class GameAbility : public Base
	{
	public:
		GameAbility();
		virtual ~GameAbility() override = default;
	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}