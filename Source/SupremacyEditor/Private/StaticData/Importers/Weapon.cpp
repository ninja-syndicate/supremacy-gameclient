
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

bool StaticDataImporter::Skin::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataSkin* Record = DataAsset->GetOrCreateWeapon(ID);

	Record->Label = RowCells[2];

	SetAssetName(DataAsset, Record, TEXT("Weapon"));
	return true;
}
