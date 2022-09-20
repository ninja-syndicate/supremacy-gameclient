#include "BattleAbility.h"

StaticDataImporter::BattleAbility::BattleAbility(): Base()
{
	this->FileName = "battle_abilities.csv";
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

	Record->Label = RowCells[1];
	if(!ParseInt(RowCells[2], "cooldown seconds", Record->Cooldown)) return false;
	Record->Description = RowCells[3];
	Record->KillingPowerLevel = RowCells[4];
	if(!ParseInt(RowCells[5], "max commander count", Record->MaximumCommanderCount)) return false;
	
	SetAssetName(DataAsset, Record, TEXT("Battle Ability"));
	return true;
}
