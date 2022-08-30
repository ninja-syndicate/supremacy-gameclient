﻿#pragma once

#include "Base.h"
#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class WarMachineModel : public Base
	{
	public:
		WarMachineModel();
		virtual ~WarMachineModel() override = default;

	protected:
		virtual bool HandleRow(UStaticData* DataAsset, TArray<FString> RowCells) override;
	};
}
