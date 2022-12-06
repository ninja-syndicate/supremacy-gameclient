#include "Faction.h"

#include "SupremacyEditorModule.h"

StaticDataImporter::Faction::Faction(): Base()
{
	this->FileName = "factions.csv";
	this->FileHeaders = {   
		"id",
		"vote_price",
		"contract_reward",
		"label",
		"guild_id",
		"deleted_at",
		"updated_at",
		"created_at",
		"logo_url",
		"background_url",
		"description",
	};
}

bool StaticDataImporter::Faction::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;
	
	UStaticDataFaction* Record = DataAsset->GetOrCreateFaction(ID);
	Record->Label = RowCells[3];
	Record->Description = RowCells[10];

	Record->LogoURL = RowCells[8];
	Record->BackgroundURL = RowCells[9];

	Record->Palette = DataAsset->GetFactionPalette(ID);
	if (Record->Palette)
	{
		// Update Palette asset name (since there is no label in it's csv)
		Record->Palette->Label = Record->Label;
		SetAssetName(DataAsset, Record->Palette, TEXT("FactionPalette"));
	}
	
	SetAssetName(DataAsset, Record, TEXT("Faction"));
	return true;
}
