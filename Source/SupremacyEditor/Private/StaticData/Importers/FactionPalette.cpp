#include "FactionPalette.h"

#include "SupremacyEditorModule.h"

StaticDataImporter::FactionPalette::FactionPalette(): Base()
{
	this->FileName = "faction_palettes.csv";
	this->FileHeaders = {   
		"faction_id",
		"primary",
		"text",
		"background",
		"s100",
		"s200",
		"s300",
		"s400",
		"s500",
		"s600",
		"s700",
		"s800",
		"s900",
	};
}

bool StaticDataImporter::FactionPalette::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;
	
	UStaticDataFactionPalette* Record = DataAsset->GetOrCreateFactionPalette(ID);

	FColor TempColor;
	if (ParseColor(RowCells[1], "primary", TempColor)) Record->Primary = TempColor;
	if (ParseColor(RowCells[2], "text", TempColor)) Record->Primary = TempColor;
	if (ParseColor(RowCells[3], "background", TempColor)) Record->Primary = TempColor;
	
	if (ParseColor(RowCells[4], "s100", TempColor)) Record->S100 = TempColor;
	if (ParseColor(RowCells[5], "s200", TempColor)) Record->S200 = TempColor;
	if (ParseColor(RowCells[6], "s300", TempColor)) Record->S300 = TempColor;
	if (ParseColor(RowCells[7], "s400", TempColor)) Record->S400 = TempColor;
	if (ParseColor(RowCells[8], "s500", TempColor)) Record->S500 = TempColor;
	if (ParseColor(RowCells[9], "s600", TempColor)) Record->S600 = TempColor;
	if (ParseColor(RowCells[10], "s700", TempColor)) Record->S700 = TempColor;
	if (ParseColor(RowCells[11], "s800", TempColor)) Record->S800 = TempColor;
	if (ParseColor(RowCells[12], "s900", TempColor)) Record->S900 = TempColor;
	
	SetAssetName(DataAsset, Record, TEXT("FactionPalette"));
	return true;
}
