#include "Skin.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataWarMachineModel.h"
#include "Types/WarMachineType.h"
#include "Types/WarMachineBoostStat.h"
#include "Types/WarMachinePowerCoreSize.h"

StaticDataImporter::Skin::Skin(): Base()
{
	this->FileName = "mech_skins.csv";
	this->FileHeaders = {   
		"id",
		"collection",
		"label",
		"tier",
		"created_at",
		"stat_modifier",
		"image_url",
		"animation_url",
		"card_animation_url",
		"large_image_url",
		"avatar_url",
		"background_color",
		"youtube_url",
		"blueprint_weapon_skin_id"
	};
}

bool StaticDataImporter::Skin::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataSkin* Record = DataAsset->GetOrCreateSkin(ID);

	Record->Collection = RowCells[1];
	Record->Label = RowCells[2];
	Record->Tier = RowCells[3];
	Record->CreatedAt = RowCells[4];
	if(!ParseInt(RowCells[5], "stat modifier", Record->StatModifier)) return false;
	ParseGuid(RowCells[13], "compatible weapon id", Record->CompatibleWeaponID);

	SetAssetName(DataAsset, Record, TEXT("W.M. Skin"));
	return true;
}
