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
	if (!ParseGuid(RowCells[0], ID)) return false;
	
	UStaticDataFaction* Record = DataAsset->GetOrCreateFaction(ID);
	Record->Label = RowCells[3];
	Record->Description = RowCells[13];

	const FString AssetName = FString::Format(TEXT("Faction - {0}"), {Record->Label});
	Record->Rename(*AssetName, DataAsset);
	
	return true;
}
