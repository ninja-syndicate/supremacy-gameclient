#include "Weapon.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "StaticData/StaticDataWeapon.h"

StaticDataImporter::Weapon::Weapon(): Base()
{
	this->FileName = "weapons.csv";
	this->FileHeaders = {
		"id",
		"brand_id",
		"label",
		"weapon_type",
		"default_skin_id",
		"damage",
		"damage_falloff",
		"damage_falloff_rate",
		"radius",
		"radius_damage_falloff",
		"spread",
		"rate_of_fire",
		"projectile_speed",
		"max_ammo",
		"is_melee",
		"energy_cost",
		"game_client_weapon_id",
		"collection",
		"default_damage_type",
		"projectile_amount",
		"dot_tick_damage",
		"dot_max_ticks",
		"is_arced",
		"charge_time_seconds",
		"burst_rate_of_fire",
		"power_instant_drain"
	};
}

FString BlueprintPathForWeapon(UStaticDataWeapon* Weapon, FString &WeaponTypeString) {
	FString Path;

	if (Weapon->Brand->ID == FGuid("2b203c87-ad8c-4ce2-af17-e079835fdbcb")) Path.Append(FString("/Game/Blueprints/Weapons/GenesisWeapons/Zaibatsu"));
	else if (Weapon->Brand->ID == FGuid("953ad4fc-3aa9-471f-a852-f39e9f36cd04")) Path.Append(FString("/Game/Blueprints/Weapons/GenesisWeapons/RedMountain"));
	else if (Weapon->Brand->ID == FGuid("009f71fc-3594-4d24-a6e2-f05070d66f40")) Path.Append(FString("/Game/Blueprints/Weapons/GenesisWeapons/Boston"));
	else if (Weapon->Brand->ID == FGuid("cb84390c-591e-4ac0-a8b4-d283c83504a4")) Path.Append(FString("/Game/Blueprints/Weapons/Nexus_Weapons/ArchonMilitech"));
	else if (Weapon->Brand->ID == FGuid("953b230b-91ef-4949-b831-165b2b9f2ba8")) Path.Append(FString("/Game/Blueprints/Weapons/Nexus_Weapons/Warsui"));
	else if (Weapon->Brand->ID == FGuid("0eb63669-3c98-4467-97af-dabc2acc43a6")) Path.Append(FString("/Game/Blueprints/Weapons/Nexus_Weapons/Pyro"));

	switch (Weapon->Type) {
	case EWeaponType::EWeaponType_Minigun:
		WeaponTypeString = FString("Minigun");
		break;
	case EWeaponType::EWeaponType_PlasmaGun:
		if (Weapon->Brand->ID == FGuid("cb84390c-591e-4ac0-a8b4-d283c83504a4"))
			WeaponTypeString = FString("PlasmaRifle");
		else
			WeaponTypeString = FString("PlasmaGun");
		break;
	case EWeaponType::EWeaponType_Flak:
		if (Weapon->Brand->ID == FGuid("0eb63669-3c98-4467-97af-dabc2acc43a6") || Weapon->Brand->ID == FGuid("cb84390c-591e-4ac0-a8b4-d283c83504a4"))
			WeaponTypeString = FString("Shotgun");
		else
			WeaponTypeString = FString("FlakGun");
		break;
	case EWeaponType::EWeaponType_MachineGun:
		WeaponTypeString = FString("MachineGun");
		break;
	case EWeaponType::EWeaponType_MissileLauncher:
		WeaponTypeString = FString("MissileLauncher");
		break;
	case EWeaponType::EWeaponType_LaserBeam:
		WeaponTypeString = FString("LaserBeam");
		break;
	case EWeaponType::EWeaponType_Cannon:
		WeaponTypeString = FString("Cannon");
		break;
	case EWeaponType::EWeaponType_GrenadeLauncher:
		WeaponTypeString = FString("GrenadeLauncher");
		break;
	case EWeaponType::EWeaponType_BFG:
		WeaponTypeString = FString("BFG");
		break;
	case EWeaponType::EWeaponType_Flamethrower:
		WeaponTypeString = FString("Flamethrower");
		break;
	case EWeaponType::EWeaponType_Sword:
		WeaponTypeString = FString("Sword");
		break;
	case EWeaponType::EWeaponType_SniperRifle:
		WeaponTypeString = FString("Fire-Sniper");
		break;
	case EWeaponType::EWeaponType_Rifle:
		WeaponTypeString = FString("Plasma-Rifle");
		break;
	case EWeaponType::EWeaponType_LightningGun:
		WeaponTypeString = FString("LightningGun");
		break;
	}

	return Path;
}

bool StaticDataImporter::Weapon::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataWeapon* Record = DataAsset->GetOrCreateWeapon(ID);

	if (!ParseGuid(RowCells[1], TEXT("brand id"), ID)) return false;
	UStaticDataBrand* Brand = DataAsset->GetBrand(ID);

	if(!Brand) 
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find brand {1} on line {2}"), {
			FileName, RowCells[1], Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->Brand = Brand;
	
	Record->Label = RowCells[2];

	if(!StringToEWeaponType.Contains(RowCells[3])) 
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find weapon type {1} on line {2}"), {
			FileName, RowCells[3], Importer.GetCurrentIndex() + 1
		});
		return false;
	}
	
	Record->Type = StringToEWeaponType[RowCells[3]];

	if (!ParseGuid(RowCells[4], TEXT("default skin id"), ID)) return false;
	UStaticDataWeaponSkin *Skin = DataAsset->GetWeaponSkin(ID);
	
	if(!Skin)
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find weapon skin {1} on line {2}"), {
			FileName, ID.ToString(), Importer.GetCurrentIndex() + 1
		});
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorReason);
		//return false;
	}
	else
	{
		Record->DefaultSkin = Skin;
	}

	if(!ParseFloat(RowCells[5], "damage", Record->Damage)) return false;
	if(!ParseFloat(RowCells[6], "damage falloff", Record->DamageFalloff)) return false;
	if(!ParseFloat(RowCells[7], "damage falloff rate", Record->DamageFalloffRate)) return false;
	if(!ParseFloat(RowCells[8], "radius", Record->Radius)) return false;
	if(!ParseFloat(RowCells[9], "radius damage falloff", Record->RadiusDamageFalloff)) return false;
	if(!ParseFloat(RowCells[10], "spread", Record->Spread)) return false;
	if(!ParseFloat(RowCells[11], "rate of fire", Record->RateOfFire)) return false;
	if(!ParseFloat(RowCells[12], "projectile speed", Record->ProjectileSpeed)) return false;
	if(!ParseFloat(RowCells[13], "max ammo", Record->MaxAmmo)) return false;
	if(!ParseBool(RowCells[14], "is melee", Record->IsMelee)) return false;
	if(!ParseFloat(RowCells[15], "energy cost", Record->EnergyCost)) return false;
	if(RowCells[16].Len() > 0) ParseGuid(RowCells[16], "game client weapon id", Record->GameClientWeaponID);
	Record->Collection = RowCells[17];

	if(!StringToEWeaponDamageType.Contains(RowCells[18]))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find damage type {1} on line {2}"), {
			FileName, RowCells[18], Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->WeaponDamageType = StringToEWeaponDamageType[RowCells[18]];

	if(!ParseFloat(RowCells[19], "projectile amount", Record->ProjectileAmount)) return false;
	if(!ParseFloat(RowCells[20], "dot tick damage", Record->DotTickDamage)) return false;
	if(!ParseFloat(RowCells[21], "dot max ticks", Record->DotMaxTicks)) return false;
	if(!ParseBool(RowCells[22], "is arced", Record->IsArced)) return false;
	if(!ParseFloat(RowCells[23], "charge time seconds", Record->ChargeTimeSeconds)) return false;
	if(!ParseFloat(RowCells[24], "burst rate of fire", Record->BurstRateOfFire)) return false;
	if(!ParseBool(RowCells[25], "power instant drain", Record->PowerInstantDrain)) return false;

	SetAssetName(DataAsset, Record, TEXT("Weapon"));

	if(Record->ID == FGuid("41099781-8586-4783-9d1c-b515a386fe9f")) {
		Record->Blueprint = TSoftClassPtr<AWeapon>(FString("Blueprint'/Game/Blueprints/Weapons/RocketPods.RocketPods'"));
	} else if (Record->ID == FGuid("e9fc2417-6a5b-489d-b82e-42942535af90")) {
		Record->Blueprint = TSoftClassPtr<AWeapon>(FString("Blueprint'/Game/Blueprints/Weapons/RocketPods.RocketPods'"));
	} else {
		FString WeaponTypeString;
		FString BlueprintPath = BlueprintPathForWeapon(Record, WeaponTypeString);
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		TArray<FAssetData> AssetData;
		AssetRegistryModule.Get().GetAssetsByPath(FName(*BlueprintPath), AssetData, false, false);

		bool Found = false;
		for (int32 i = 0; i < AssetData.Num(); i++) {
			if (AssetData[i].AssetName.ToString().Contains(WeaponTypeString)) {
				UE_LOG(LogTemp, Warning, TEXT("%s %s -> %s"), *Record->Label, *WeaponTypeString, *(AssetData[i].AssetName.ToString()));
				Record->Blueprint = TSoftClassPtr<AWeapon>(FString("Blueprint'") + AssetData[i].ObjectPath.ToString() + FString("'"));
				Found = true;
				break;
			}
		}
	}

	return true;
}
