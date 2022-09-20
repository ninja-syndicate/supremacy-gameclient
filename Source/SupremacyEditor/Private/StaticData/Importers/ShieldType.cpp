#include "ShieldType.h"

StaticDataImporter::ShieldType::ShieldType() : Base()
{
	this->FileName = "shield_types.csv";
	this->FileHeaders = {
		"id",
		"label",
		"description",
	};
}

bool StaticDataImporter::ShieldType::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataShieldType* Record = DataAsset->GetOrCreateShieldType(ID);

	Record->Label = RowCells[1];
	Record->Description = RowCells[2];

	SetAssetName(DataAsset, Record, TEXT("Brand"));
	return true;
}
