#include "MechSkinCompatibility.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataMechSkinCompatibility.h"

StaticDataImporter::MechSkinCompatibility::MechSkinCompatibility(): Base()
{
	this->FileName = "mech_model_skin_compatibilities.csv";
	this->FileHeaders = {
		"mech_skin_id",
		"mech_model",
		"image_url",
		"animation_url",
		"card_animation_url",
		"large_image_url",
		"avatar_url",
		"created_at",
		"background_color",
		"youtube_url"
	};
}

bool StaticDataImporter::MechSkinCompatibility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid SkinId, MechId;

	if(!ParseGuid(RowCells[0], "skin id", SkinId)) return false;
	if(!ParseGuid(RowCells[1], "mech id", MechId)) return false;

	FGuid Id;
	if(!CombineGuidsUnique(SkinId, MechId, Id)) return false;
	
	UStaticDataMechSkinCompatibility *Record = DataAsset->GetOrCreateMechSkinCompatibility(Id);
	
	Record->Skin = DataAsset->GetSkin(SkinId);
	Record->WarMachineModel = DataAsset->GetWarMachineModel(MechId);

	Record->Label = Record->WarMachineModel->Label + " -> " + Record->Skin->Label;
	
	SetAssetName(DataAsset, Record, TEXT("Mech Skin Compatibility"));
	return true;
}
