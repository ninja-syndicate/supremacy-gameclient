#include "WeaponSkin.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataWarMachineModel.h"
#include "Types/WarMachineType.h"
#include "Types/WarMachineBoostStat.h"
#include "Types/WarMachinePowerCoreSize.h"

StaticDataImporter::WeaponSkin::WeaponSkin(): Base()
{
	this->FileName = "weapon_skins.csv";
	this->FileHeaders = {   
		"id",
		"label",
		"tier",
		"created_at",
		"collection",
		"stat_modifier",
		"image_url",
		"animation_url",
		"card_animation_url",
		"large_image_url",
		"avatar_url",
		"background_color",
		"youtube_url"
	};
}

bool StaticDataImporter::WeaponSkin::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataWeaponSkin* Record = DataAsset->GetOrCreateWeaponSkin(ID);

	Record->Collection = RowCells[4];
	Record->Label = RowCells[1];
	Record->Tier = RowCells[2];
	Record->CreatedAt = RowCells[3];
	ParseInt(RowCells[5], "stat modifier", Record->StatModifier);

	SetAssetName(DataAsset, Record, TEXT("Weapon Skin"));
	return true;
}
