#include "WarMachineModel.h"

#include "SupremacyEditorModule.h"
#include "StaticData/StaticDataWarMachineModel.h"
#include "Types/WarMachineType.h"

StaticDataImporter::WarMachineModel::WarMachineModel(): Base()
{
	this->FileName = "mech_models.csv";
	this->FileHeaders = {   
		"id",
		"label",
		"created_at",
		"default_chassis_skin_id",
		"brand_id",
		"mech_type",
	};
}

bool StaticDataImporter::WarMachineModel::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataWarMachineModel* Record = DataAsset->GetOrCreateWarMachineModel(ID);
	Record->Label = RowCells[1];

	if (!StringToEWarMachineModelType.Contains(RowCells[5].ToUpper()))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find mech type {1} on line {2}"), {
			FileName, RowCells[5], Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->Type = StringToEWarMachineModelType[RowCells[5].ToUpper()];

	if (!ParseGuid(RowCells[4], TEXT("brand id"), ID)) return false;
	UStaticDataBrand* Brand = DataAsset->GetBrand(ID);

	if (Brand == nullptr)
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find brand with {1} on line {2}"), {
			FileName, ID.ToString(), Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->Brand = Brand;

	SetAssetName(DataAsset, Record, TEXT("W.M. Model"));
	return true;
}
