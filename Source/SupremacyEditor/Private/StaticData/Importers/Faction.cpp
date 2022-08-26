#include "Faction.h"

#include "SupremacyEditorModule.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"

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
	if (!FGuid::Parse(RowCells[0], ID))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to parse id on line {1}"), {
			FileName, Importer.GetCurrentIndex() + 1
		});
		return false;
	}
	
	FStaticDataFaction record = DataAsset->GetOrCreateFaction(ID);
	record.Label = RowCells[3];
	record.Description = RowCells[13];

	DataAsset->UpdateFaction(record);
	return true;
}
