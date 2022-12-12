#include "WeaponSkinCompatibility.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Types/WeaponType.h"

StaticDataImporter::WeaponSkinCompatibility::WeaponSkinCompatibility() : Base()
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

FString MaterialsPathForWeapon(const UStaticDataWeapon* Weapon, const UStaticDataWeaponSkin *WeaponSkin) {
	FString Path;

	bool IsArchon = false;

	// Genesis Rocket Pods don't have models/materials
	if (Weapon->ID == FGuid("e9fc2417-6a5b-489d-b82e-42942535af90") ||
		Weapon->ID == FGuid("41099781-8586-4783-9d1c-b515a386fe9f") ||
		Weapon->ID == FGuid("c1c78867-9de7-43d3-97e9-91381800f38e"))
	{
		return "";
	}

	if (Weapon->Brand->ID == FGuid("953ad4fc-3aa9-471f-a852-f39e9f36cd04")) Path.Append(FString("/Game/Weapons/GenesisWeapons/RedMountain"));
	else if (Weapon->Brand->ID == FGuid("009f71fc-3594-4d24-a6e2-f05070d66f40")) Path.Append(FString("/Game/Weapons/GenesisWeapons/BostonCybernetics"));
	else if (Weapon->Brand->ID == FGuid("2b203c87-ad8c-4ce2-af17-e079835fdbcb")) Path.Append(FString("/Game/Weapons/GenesisWeapons/Zaibatsu"));
	else if (Weapon->Brand->ID == FGuid("cb84390c-591e-4ac0-a8b4-d283c83504a4")) {
		Path.Append(FString("/Game/Weapons/Nexus_Weapons/ArchonMilitech")); 
		IsArchon = true;
	}
	else if (Weapon->Brand->ID == FGuid("953b230b-91ef-4949-b831-165b2b9f2ba8")) Path.Append(FString("/Game/Weapons/Nexus_Weapons/Warsui"));
	else if (Weapon->Brand->ID == FGuid("0eb63669-3c98-4467-97af-dabc2acc43a6")) {
		Path.Append(FString("/Game/Weapons/Nexus_Weapons/Pyro"));
		IsArchon = true;
	}

	if (Weapon->Brand->ID == FGuid("2b203c87-ad8c-4ce2-af17-e079835fdbcb")) {
		Path.Append("/Materials_Both");
	}
	else
	{
		switch (Weapon->Type) {
		case EWeaponType::EWeaponType_Minigun:
			Path.Append(FString("/Minigun"));
			break;
		case EWeaponType::EWeaponType_PlasmaGun:
			Path.Append(IsArchon ? FString("/PlasmaRifle") : FString("/PlasmaGun"));
			break;
		case EWeaponType::EWeaponType_Flak:
			Path.Append(FString("/FlakGun"));
			break;
		case EWeaponType::EWeaponType_MachineGun:
			Path.Append(FString("/MachineGun"));
			break;
		case EWeaponType::EWeaponType_MissileLauncher:
		case EWeaponType::EWeaponType_RocketPods: // TODO: Rename MissileLauncher folder to RocketPods
			Path.Append(FString("/MissileLauncher"));
			break;
		case EWeaponType::EWeaponType_LaserBeam:
			Path.Append(FString("/LaserBeam"));
			break;
		case EWeaponType::EWeaponType_Cannon:
			Path.Append(FString("/Cannon"));
			break;
		case EWeaponType::EWeaponType_GrenadeLauncher:
			Path.Append(FString("/GrenadeLauncher"));
			break;
		case EWeaponType::EWeaponType_BFG:
			Path.Append(FString("/BFG"));
			break;
		case EWeaponType::EWeaponType_Flamethrower:
			Path.Append(FString("/Flamethrower"));
			break;
		case EWeaponType::EWeaponType_Sword:
			Path.Append(FString("/Sword"));
			break;
		case EWeaponType::EWeaponType_SniperRifle:
			Path.Append(FString("/Minigun"));
			break;
		case EWeaponType::EWeaponType_Rifle:
			Path.Append(FString("/PlasmaRifle"));
			break;
		case EWeaponType::EWeaponType_LightningGun:
			Path.Append(FString("/LightningGun"));
			break;
		default: ;
		}

		Path.Append("/Materials");
	}

	FString SkinName = WeaponSkin->Label.Replace(TEXT(" "), TEXT(""));
	if (SkinName == TEXT("Less-Than-Lethal")) {
		SkinName = TEXT("LessThanLethal");
	}

	Path.Append(FString("/") + SkinName);

	return Path;
}

FAssetData* GetWeaponMaterialForSlot(TArray<FAssetData>& Materials, const FString Slot) 
{
	for (int32 i = 0; i < Materials.Num(); i++) {
		if (Materials[i].AssetName.ToString().ToLower().Contains(Slot.ToLower())) return &Materials[i];
	}
	return nullptr;
}

bool StaticDataImporter::WeaponSkinCompatibility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid SkinId, WeaponId;

	if(!ParseGuid(RowCells[0], "skin id", SkinId)) return false;
	if(!ParseGuid(RowCells[1], "weapon id", WeaponId)) return false;

	FGuid Id;
	if(!CombineGuidsUnique(SkinId, WeaponId, Id)) return false;
	
	UStaticDataWeaponSkinCompatibility *Record = DataAsset->GetOrCreateWeaponSkinCompatibility(Id);
	
	Record->WeaponSkin = DataAsset->GetWeaponSkin(SkinId);
	Record->Weapon = DataAsset->GetWeapon(WeaponId);

	Record->Label = Record->Weapon->Label + " -> " + Record->WeaponSkin->Label;

	const FString MaterialsPath = MaterialsPathForWeapon(Record->Weapon, Record->WeaponSkin);
	if (MaterialsPath == "")
		return true;
	
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByPath(FName(*MaterialsPath), AssetData, false, false);
	if (AssetData.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: found no material files"), *MaterialsPath);
		return false;
	}
	
	int32 AssetIndex = 0;
	if (AssetData.Num() >= 2 && WeaponId == FGuid("536831f0-799b-4fd1-ba70-023a98d53668"))
	{
		// BFG has 2 materials
		const FAssetData* BfgMaterial = GetWeaponMaterialForSlot(AssetData, "AM_BFG_Base");
		if (BfgMaterial)
			Record->Materials.Add("AM_BFG", TSoftObjectPtr<UMaterial>(FString(FString("Material'") + BfgMaterial->GetObjectPathString() + FString("'"))));
		const FAssetData* BfgTubesMaterial = GetWeaponMaterialForSlot(AssetData, "AM_BFG_Tubes");
		if (BfgTubesMaterial)
			Record->Materials.Add("AM_BFG_Tubes", TSoftObjectPtr<UMaterial>(FString(FString("Material'") + BfgTubesMaterial->GetObjectPathString() + FString("'"))));
	}
	else
	{
		Record->Materials.Add("mat", TSoftObjectPtr<UMaterial>(FString(FString("Material'") + AssetData[AssetIndex].GetObjectPathString() + FString("'"))));
	}
	
	SetAssetName(DataAsset, Record, TEXT("Weapon Skin Compatibility"));
	return true;
}
