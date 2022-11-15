﻿#include "WarMachineModel.h"

#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"
#include "StaticData/StaticDataWarMachineModel.h"
#include "Types/WarMachineType.h"
#include "Types/WarMachineBoostStat.h"
#include "Types/WarMachinePowerCoreSize.h"

StaticDataImporter::WarMachineModel::WarMachineModel(): Base()
{
	this->FileName = "mechs.csv";
	this->FileHeaders = {   
		"id",
		"label",
		"created_at",
		"default_chassis_skin_id",
		"brand_id",
		"mech_type",
		"boost_stat",
		"weapon_hardpoints",
		"utility_slots",
		"speed",
		"max_hitpoints",
		"power_core_size",
		"collection",
		"availability_id",
		"max_shield",
		"shield_recharge_rate",
		"shield_recharge_power_cost",
		"shield_type_id",
		"shield_recharge_delay",
		"height_meters",
		"walk_speed_modifier",
		"sprint_spread_modifier",
		"idle_drain",
		"walk_drain",
		"run_drain"

	};
}

TSoftClassPtr<AMech> MechFromId(FString ID)
{
	if(ID == "5d3a973b-c62b-4438-b746-d3de2699d42a") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Genesis_Mechs/NewGenesisMechs/NewMech_Boston.NewMech_Boston_C'"));
	if(ID == "ac27f3b9-753d-4ace-84a9-21c041195344") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Genesis_Mechs/NewGenesisMechs/NewMech_RedMountain.NewMech_RedMountain_C'"));
	if(ID == "625cd381-7c66-4e2f-9f69-f81589105730") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Genesis_Mechs/NewGenesisMechs/NewMech_Zaibatsu.NewMech_Zaibatsu_C'"));
	if(ID == "02ba91b7-55dc-450a-9fbd-e7337ae97a2b") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Humanoid_Dais_WarEnforcer.Mech_Humanoid_Dais_WarEnforcer_C'"));
	if(ID == "7068ab3e-89dc-4ac1-bcbb-1089096a5eda") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Platform_Dais_Annihilator.Mech_Platform_Dais_Annihilator_C'"));
	if(ID == "3dc5888b-f5ff-4d08-a520-26fd3681707f") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Humanoid_X3_Kenji.Mech_Humanoid_X3_Kenji_C'"));
	if(ID == "0639ebde-fbba-498b-88ac-f7122ead9c90") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Platform_X3_Shirokuma.Mech_Platform_X3_Shirokuma_C'"));
	if(ID == "fc9546d0-9682-468e-af1f-24eb1735315b") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Humanoid_UMC_Aries.Mech_Humanoid_UMC_Aries_C'"));
	if(ID == "df1ac803-0a90-4631-b9e0-b62a44bdadff") return TSoftClassPtr<AMech>(FSoftClassPath(
		"Blueprint'/Game/Mechs/Nexus_Mechs/Mech_Platform_UMC_Viking.Mech_Platform_UMC_Viking_C'"));
	return TSoftClassPtr<AMech>();
}

bool StaticDataImporter::WarMachineModel::HandleRow(UStaticData* DataAsset, TArray<FString> RowCells)
{
	FGuid ID;
	if (!ParseGuid(RowCells[0], TEXT("id"), ID)) return false;

	UStaticDataWarMachineModel* Record = DataAsset->GetOrCreateWarMachineModel(ID);
	Record->Label = RowCells[1];
	Record->UnrealWarMachine = MechFromId(RowCells[0]);

	if (!StringToEWarMachineModelType.Contains(RowCells[5].ToUpper()))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find mech type {1} on line {2}"), {
			FileName, RowCells[5], Importer.GetCurrentIndex() + 1
		});
		return false;
	}
	
	Record->Type = StringToEWarMachineModelType[RowCells[5].ToUpper()];

	if(!StringToEWarMachineBoostStat.Contains(RowCells[6].ToUpper()))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find mech boost stat {1} on line {2}"), {
			FileName, RowCells[6], Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->BoostStat = StringToEWarMachineBoostStat[RowCells[6].ToUpper()];

	if(!StringToEWarMachinePowerCoreSize.Contains(RowCells[11].ToUpper()))
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find mech power core size {1} on line {2}"), {
			FileName, RowCells[11], Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->Collection = RowCells[12];
	
	Record->PowerCoreSize = StringToEWarMachinePowerCoreSize[RowCells[11].ToUpper()];
	
	if(!ParseInt(RowCells[7], "hard point count", Record->WeaponHardpointCount)) return false;
	if(!ParseInt(RowCells[8], "utility slot count", Record->UtilitySlotCount)) return false;
	if(!ParseInt(RowCells[9], "speed", Record->Speed)) return false;
	if(!ParseInt(RowCells[10], "max hitpoints", Record->MaxHitpoints)) return false;

	Record->CreatedAt = RowCells[2];

	if(!ParseFloat(RowCells[14], "max shield", Record->MaxShield)) return false;
	if(!ParseFloat(RowCells[15], "shield recharge rate", Record->ShieldRechargeRate)) return false;
	if(!ParseFloat(RowCells[16], "shield recharge power cost", Record->ShieldRechargePowerCost)) return false;
	
	if (!ParseFloat(RowCells[18], "shield recharge delay", Record->ShieldRechargeDelay)) return false;
	if (!ParseFloat(RowCells[19], "height meters", Record->Height)) return false;

	if (!ParseFloat(RowCells[20], "walk speed modifier", Record->WalkSpeedModifier)) return false;
	if (!ParseFloat(RowCells[21], "sprint spread modifier", Record->SprintSpreadModifier)) return false;
	if (!ParseFloat(RowCells[22], "idle drain", Record->IdleDrain)) return false;
	if (!ParseFloat(RowCells[23], "walk drain", Record->WalkDrain)) return false;
	if (!ParseFloat(RowCells[24], "run drain", Record->RunDrain)) return false;

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

	if(!ParseGuid(RowCells[3], TEXT("default skin id"), ID)) return false;
	UStaticDataSkin* Skin = DataAsset->GetSkin(ID);

	if(!Skin)
	{
		ErrorReason = FString::Format(TEXT("{0} - unable to find skin with {1} on line {2}"), {
			FileName, ID.ToString(), Importer.GetCurrentIndex() + 1
		});
		return false;
	}

	Record->DefaultSkin = Skin;
	
	SetAssetName(DataAsset, Record, TEXT("W.M. Model"));
	return true;
}
