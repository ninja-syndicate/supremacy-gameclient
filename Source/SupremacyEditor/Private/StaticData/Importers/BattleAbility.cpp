#include "BattleAbility.h"

StaticDataImporter::BattleAbility::BattleAbility(): Base()
{
	this->FileName = "brands.csv";
	this->FileHeaders = {
		"id",
		"label",
		"cooldown_duration_second",
		"description",
		"killing_power_level",
		"maximum_commander_count"
	};
}

bool StaticDataImporter::BattleAbility::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataBattleAbility* Record = DataAsset->GetOrCreateBattleAbility(ID);
	
	
	
	SetAssetName(DataAsset, Record, TEXT("Battle Ability"));
	return true;
}
