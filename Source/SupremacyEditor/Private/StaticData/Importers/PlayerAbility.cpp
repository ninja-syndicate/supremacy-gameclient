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

	if (!ParseInt(RowCells[1], "game client ability id", Record->GameClientAbilityID)) return false;
	Record->Label = RowCells[2];
	if (!ParseColor(RowCells[3], "colour", Record->Colour)) return false;
	Record->ImageURL = RowCells[4];
	Record->Description = RowCells[5];
	if (!ParseColor(RowCells[6], "text colour", Record->TextColour)) return false;
	Record->LocationSelectType = RowCells[7];
	Record->CreatedAt = RowCells[8];
	Record->RarityWeight = RowCells[9];
	if (!ParseInt(RowCells[10], "inventory limit", Record->InventoryLimit)) return false;
	if (!ParseInt(RowCells[11], "cooldown seconds", Record->CooldownSeconds)) return false;
	if (!ParseBool(RowCells[12], "display on minimap", Record->DisplayOnMinimap)) return false;
	if (!ParseInt(RowCells[13], "launching delay seconds", Record->LaunchingDelaySeconds)) return false;
	Record->MinimapDisplayEffectType = RowCells[14];
	Record->MechDisplayEffectType = RowCells[15];
	if (!ParseInt(RowCells[16], "animation duration seconds", Record->AnimationDurationSeconds)) return false;
		
	SetAssetName(DataAsset, Record, TEXT("Player Ability"));
	return true;
}
