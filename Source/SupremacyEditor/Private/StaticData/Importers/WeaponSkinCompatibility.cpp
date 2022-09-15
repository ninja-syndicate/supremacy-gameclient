#include "WeaponSkinCompatibility.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataMechSkinCompatibility.h"

StaticDataImporter::WeaponSkinCompatibility::WeaponSkinCompatibility(): Base()
{
	this->FileName = "weapon_model_skin_compatibilities.csv";
	this->FileHeaders = {
		"blueprint_weapon_skin_id",
		"weapon_model_id",
		"image_url",
		"card_animation_url",
		"avatar_url",
		"large_image_url",
		"background_color",
		"animation_url",
		"youtube_url"
	};
}

bool StaticDataImporter::WeaponSkinCompatibility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid SkinId, WeaponId;

	if(!ParseGuid(RowCells[0], "skin id", SkinId)) return false;
	if(!ParseGuid(RowCells[1], "weapon id", WeaponId)) return false;

	FGuid Id;
	if(!CombineGuidsUnique(SkinId, WeaponId, Id)) return false;
	
	UStaticDataWeaponSkinCompatibility *Record = DataAsset->GetOrCreateWeaponSkinCompatibility(Id);
	
	Record->Label = Id.ToString();
	Record->WeaponSkin = DataAsset->GetWeaponSkin(SkinId);
	Record->Weapon = DataAsset->GetWeapon(WeaponId);
	
	SetAssetName(DataAsset, Record, TEXT("Weapon Skin Compatibility"));
	return true;
}
