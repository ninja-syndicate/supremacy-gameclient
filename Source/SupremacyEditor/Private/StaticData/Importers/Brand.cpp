#include "Brand.h"

StaticDataImporter::Brand::Brand(): Base()
{
	this->FileName = "brands.csv";
	this->FileHeaders = {
		"id",
		"faction_id",
		"label",
		"deleted_at",
		"updated_at",
		"created_at",
	};
}

bool StaticDataImporter::Brand::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataBrand* Record = DataAsset->GetOrCreateBrand(ID);
	if (!ParseGuid(RowCells[1], TEXT("faction id"), ID)) return false;

	UStaticDataFaction* Faction = DataAsset->GetFaction(ID);
	if (Faction == nullptr)
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find faction with {1} on line {2}"), {
			FileName, ID.ToString(), Importer.GetCurrentIndex() + 1
		});
		return false;
	}
	Record->Faction = Faction;
	Record->Label = RowCells[2];

	SetAssetName(DataAsset, Record, TEXT("Brand"));
	return true;
}
