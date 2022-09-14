#include "Weapon.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
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

	if (!ParseGuid(RowCells[0], TEXT("default skin id"), ID)) return false;
	UStaticDataSkin *Skin = DataAsset->GetSkin(ID);
	
	if(!Skin)
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find skin {1} on line {2}"), {
			FileName, ID.ToString(), Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->DefaultSkin = Skin;

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
	if(!ParseFloat(RowCells[25], "power instant drain", Record->PowerInstantDrain)) return false;

	SetAssetName(DataAsset, Record, TEXT("Weapon"));
	return true;
}
