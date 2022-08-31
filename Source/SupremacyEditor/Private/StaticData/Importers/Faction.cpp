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
		"primary_color",
		"secondary_color",
		"background_color",
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
	Record->Description = RowCells[13];

	Record->LogoURL = RowCells[11];
	Record->BackgroundURL = RowCells[12];

	FColor tempColor;
	if (ParseColor(RowCells[8], "primary color", tempColor)) Record->PrimaryColor = tempColor;

	if (ParseColor(RowCells[9], "secondary color", tempColor)) Record->SecondaryColor = tempColor; 

	if (ParseColor(RowCells[10], "background color", tempColor)) Record->BackgroundColor = tempColor;
	
	SetAssetName(DataAsset, Record, TEXT("Faction"));
	return true;
}
