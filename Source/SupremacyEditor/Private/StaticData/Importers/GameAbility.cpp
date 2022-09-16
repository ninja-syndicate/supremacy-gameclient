#include "GameAbility.h"

#include "../../../../Supremacy/Public/StaticData/StaticData.h"

StaticDataImporter::GameAbility::GameAbility(): Base()
{
	this->FileName = "game_abilities.csv";
	this->FileHeaders = {
		"id",
		"game_client_ability_id",
		"faction_id",
		"battle_ability_id",
		"label",
		"colour",
		"image_url",
		"sups_cost",
		"description",
		"text_colour",
		"current_sups",
		"level",
		"location_select_type",
		"deleted_at",
		"launching_delay_seconds",
		"display_on_mini_map",
		"mini_map_display_effect_type",
		"mech_display_effect_type",
		"animation_duration_seconds",
		"should_check_team_kill",
		"maximum_team_kill_tolerant_count",
		"ignore_self_kill"
	};
}

bool StaticDataImporter::GameAbility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataGameAbility* Record = DataAsset->GetOrCreateGameAbility(ID);

	Record->Label = RowCells[4];
	
	SetAssetName(DataAsset, Record, TEXT("Game Ability"));
	return true;
}
