#include "PlayerAbility.h"

StaticDataImporter::PlayerAbility::PlayerAbility(): Base()
{
	this->FileName = "player_abilities.csv";
	this->FileHeaders = {
		"id",
		"game_client_ability_id",
		"label",
		"colour",
		"image_url",
		"description",
		"text_colour",
		"location_select_type",
		"created_at",
		"rarity_weight",
		"inventory_limit",
		"cooldown_seconds",
		"display_on_mini_map",
		"launching_delay_seconds",
		"mini_map_display_effect_type",
		"mech_display_effect_type",
		"animation_duration_seconds"
	};
}

bool StaticDataImporter::PlayerAbility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataPlayerAbility* Record = DataAsset->GetOrCreatePlayerAbility(ID);

	Record->Label = RowCells[2];
	
	SetAssetName(DataAsset, Record, TEXT("Player Ability"));
	return true;
}
