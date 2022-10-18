#pragma once

#include "PowerCore.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataPowerCore.h"
#include "Types/WarMachinePowerCoreSize.h"

class UStaticData;

StaticDataImporter::PowerCore::PowerCore(): Base()
{
	FileName = "power_cores.csv";
	FileHeaders = {
		"id",
		"collection",
		"label",
		"size",
		"capacity",
		"max_draw_rate",
		"recharge_rate",
		"armour",
		"max_hitpoints",
		"tier",
		"created_at",
		"image_url",
		"card_animation_url",
		"avatar_url",
		"large_image_url",
		"background_color",
		"animation_url",
		"youtube_url"
	};
}

bool ::StaticDataImporter::PowerCore::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataPowerCore *Record = DataAsset->GetOrCreatePowerCore(ID);

	Record->Label = RowCells[2];
	Record->Collection = RowCells[1];

	if(!StringToEWarMachinePowerCoreSize.Contains(RowCells[3].ToUpper()))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find power core size {1} on line {2}"), {
			FileName, RowCells[3], Importer.GetCurrentIndex() + 1
		});
		return false;
	}
	
	Record->Size = StringToEWarMachinePowerCoreSize[RowCells[3]];

	if(!ParseFloat(RowCells[4], "capacity", Record->Capacity)) return false;
	if(!ParseFloat(RowCells[5], "max draw rate", Record->MaxDrawRate)) return false;
	if(!ParseFloat(RowCells[6], "recharge rate", Record->RechargeRate)) return false;
	if(!ParseFloat(RowCells[7], "armour", Record->Armour)) return false;
	if(!ParseFloat(RowCells[8], "max hitpoints", Record->MaxHitpoints)) return false;

	Record->Tier = RowCells[9];
	Record->CreatedAt = RowCells[10];
	
	SetAssetName(DataAsset, Record, TEXT("Power Core"));
	return true;
}