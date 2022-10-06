#include "MechSkinCompatibility.h"
#include "AssetRegistry/AssetRegistryModule.h"
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

FString MaterialsPathFromMech(FString ID, FString SkinName, bool IsGenesis)
{
	FString BasePath;

	if (ID == FString("5d3a973b-c62b-4438-b746-d3de2699d42a").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Genesis_Mechs/BostonCybernetics_MechAssets/Materials";
	if (ID == FString("ac27f3b9-753d-4ace-84a9-21c041195344").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Genesis_Mechs/RedMountain_MechAssets/Materials";
	if (ID == FString("625cd381-7c66-4e2f-9f69-f81589105730").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Genesis_Mechs/Zaibastsu_MechAssets/Materials";
	if (ID == FString("02ba91b7-55dc-450a-9fbd-e7337ae97a2b").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/DaisonAvionics_MechAssets/WarEnforcer_Humanoid_MechAssets/Materials";
	if (ID == FString("7068ab3e-89dc-4ac1-bcbb-1089096a5eda").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/DaisonAvionics_MechAssets/Annihilator_Platform_MechAssets/Materials";
	if (ID == FString("3dc5888b-f5ff-4d08-a520-26fd3681707f").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/X3WarTech_MechAssets/Kenji_HumanoidMechAssets/Materials";
	if (ID == FString("0639ebde-fbba-498b-88ac-f7122ead9c90").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/X3WarTech_MechAssets/Shirokuma_PlatformMechAssets/Materials";
	if (ID == FString("fc9546d0-9682-468e-af1f-24eb1735315b").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/UnifiedMartianCorp_MechAssets/Aries_HumanoidMechAssets/Materials";
	if (ID == FString("df1ac803-0a90-4631-b9e0-b62a44bdadff").ToUpper().Replace(TEXT("-"), TEXT(""))) BasePath = "/Game/Mechs/Nexus_Mechs/UnifiedMartianCorp_MechAssets/Viking_Platform_MechAssets/Materials";

	FString Out;
	Out.Append(BasePath);
	Out.Append("/");
	Out.Append(SkinName.Replace(TEXT(" "), TEXT("")));
	if (IsGenesis) Out.Append("_Materials");
	Out.Append("/");

	return Out;
}

bool IsGenesis(FString ID)
{
	if (ID == FString("5d3a973b-c62b-4438-b746-d3de2699d42a").ToUpper().Replace(TEXT("-"), TEXT(""))) return true;
	if (ID == FString("ac27f3b9-753d-4ace-84a9-21c041195344").ToUpper().Replace(TEXT("-"), TEXT(""))) return true;
	if (ID == FString("625cd381-7c66-4e2f-9f69-f81589105730").ToUpper().Replace(TEXT("-"), TEXT(""))) return true;
	return false;
}

FAssetData* GetMaterialForSlot(TArray<FAssetData>& Materials, FString Slot) 
{
	for (int32 i = 0; i < Materials.Num(); i++) {
		if (Materials[i].AssetName.ToString().ToLower().Contains(Slot.ToLower())) return &Materials[i];
	}
	return nullptr;
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

	FString MaterialsPath = MaterialsPathFromMech(Record->WarMachineModel->ID.ToString(), Record->Skin->Label, IsGenesis(Record->WarMachineModel->ID.ToString()));

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;

	AssetRegistryModule.Get().GetAssetsByPath(FName(*MaterialsPath), AssetData, false, false);
	if (AssetData.Num() <= 0) {
		//UE_LOG(LogTemp, Warning, TEXT("%s: found no material files"), *MaterialsPath);
	} else {
		UObject* Object = Record->WarMachineModel->SkeletalMesh.LoadSynchronous();
		if (Object) {
			USkeletalMesh* Mesh = Cast<USkeletalMesh>(Object);
			//UE_LOG(LogTemp, Warning, TEXT("loading mesh succeeded"));
			TArray<FSkeletalMaterial> Materials = Mesh->GetMaterials();
			for (int32 i = 0; i < Materials.Num(); i++)
			{
				FSkeletalMaterial Material = Materials[i];
				FAssetData* MaterialAsset = GetMaterialForSlot(AssetData, Material.MaterialSlotName.ToString());
				if (MaterialAsset) {
					Record->Materials.Add(Material.MaterialSlotName.ToString(), TSoftObjectPtr<UMaterial>(FString(FString("Material'") + MaterialAsset->ObjectPath.ToString() + FString("'"))));
				}
			}
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh %s"), *(Record->WarMachineModel->SkeletalMesh.ToString()));
		}
	}

	//for (int32 i = 0; i < AssetData.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *(AssetData[i].AssetName.ToString()));
	//}

	SetAssetName(DataAsset, Record, TEXT("Mech Skin Compatibility"));
	return true;
}
