#include "GameAbility.h"

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
		"description",
		"text_colour",
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
		"ignore_self_kill",
		"count_per_battle"
	};
}

bool StaticDataImporter::GameAbility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataGameAbility* Record = DataAsset->GetOrCreateGameAbility(ID);

	if(!ParseInt(RowCells[1], "game client ability id", Record->GameClientAbilityID)) return false;
	if(!ParseGuid(RowCells[2], "faction id", ID)) return false;
	Record->Faction = DataAsset->GetFaction(ID);
	ParseGuid(RowCells[3], "battle ability id", ID);
	Record->BattleAbility = DataAsset->GetBattleAbility(ID);
	Record->Label = RowCells[4];
	if(!ParseColor(RowCells[5], "colour", Record->Colour)) return false;
	Record->ImageURL = RowCells[6];
	//if(!ParseInt(RowCells[7], "sups cost", Record->SupsCost)) return false;
	Record->Description = RowCells[7];
	if(!ParseColor(RowCells[8], "text colour", Record->TextColour)) return false;
	//if(!ParseInt(RowCells[10], "current sups", Record->CurrentSups)) return false;
	Record->Level = RowCells[9];
	Record->LocationSelectType = RowCells[10];
	Record->DeletedAt = RowCells[11];
	if(!ParseInt(RowCells[12], "launching delay seconds", Record->LaunchingDelaySeconds)) return false;
	if(!ParseBool(RowCells[13], "display on minimap", Record->DisplayOnMinimap)) return false;
	Record->MinimapDisplayEffectType = RowCells[14];
	Record->MechDisplayEffectType = RowCells[15];
	if(!ParseInt(RowCells[16], "animation duration seconds", Record->AnimationDurationSeconds)) return false;
	if(!ParseBool(RowCells[17], "should check team kill", Record->ShouldCheckTeamKill)) return false;
	if(!ParseInt(RowCells[18], "maximum team kill tolerant amount", Record->MaximumTeamKillTolerantCount)) return false;
	if(!ParseBool(RowCells[19], "ignore self kill", Record->IgnoreSelfKill)) return false;
	if (!ParseInt(RowCells[20], "count per battle", Record->CountPerBattle)) return false;

	SetAssetName(DataAsset, Record, TEXT("Game Ability"));
	return true;
}
