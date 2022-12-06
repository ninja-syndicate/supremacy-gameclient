// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataImporter.h"
#include "SupremacyEditorModule.h"
#include "DesktopPlatformModule.h"
#include "Importers/BattleAbility.h"

#include "Importers/Faction.h"
#include "Importers/Brand.h"
#include "Importers/FactionPalette.h"
#include "Importers/MechSkinCompatibility.h"
#include "Importers/PowerCore.h"
#include "Importers/WeaponSkinCompatibility.h"
#include "Importers/WarMachineModel.h"
#include "Importers/Skin.h"
#include "Importers/Weapon.h"
#include "Importers/WeaponSkin.h"
#include "Importers/GameAbility.h"
#include "Importers/PlayerAbility.h"
#include "Importers/ShieldType.h"

UStaticDataImporter::UStaticDataImporter()
{
	Importers.Add(new StaticDataImporter::FactionPalette());
	Importers.Add(new StaticDataImporter::Faction());
	Importers.Add(new StaticDataImporter::Brand());
	Importers.Add(new StaticDataImporter::Skin());
	Importers.Add(new StaticDataImporter::WeaponSkin());
	Importers.Add(new StaticDataImporter::Weapon());
	Importers.Add(new StaticDataImporter::WarMachineModel());
	Importers.Add(new StaticDataImporter::MechSkinCompatibility());
	Importers.Add(new StaticDataImporter::WeaponSkinCompatibility());
	Importers.Add(new StaticDataImporter::PowerCore());
	Importers.Add(new StaticDataImporter::BattleAbility());
	Importers.Add(new StaticDataImporter::PlayerAbility());
	Importers.Add(new StaticDataImporter::GameAbility());
	Importers.Add(new StaticDataImporter::ShieldType());
	ImportPath = TEXT("");
	DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform == nullptr)
	{
		UE_LOG(LogSupremacyEditor, Error, TEXT("Unable to load desktop platform! This is a fatal error!"))
		return;
	}
}

UStaticDataImporter::~UStaticDataImporter()
{
	for (const auto Importer : Importers)
	{
		delete(Importer);
	}
	Importers.Reset();
}

bool UStaticDataImporter::SetImportDirectory()
{
	Ready = false;
	if (DesktopPlatform == nullptr)
	{
		LogError("Unable to load desktop platform! Can't set import directory");
		return false;
	}

	FString OutFolder;
	if (!DesktopPlatform->OpenDirectoryDialog(nullptr, "Select Static Directory", "..", OutFolder))
	{
		LogWarning("No Folder selected");
		return false;
	}

	if (!IFileManager::Get().DirectoryExists(*OutFolder))
	{
		LogWarning(FString::Printf(TEXT("No Directory found at %s"), *OutFolder));
		return false;
	}

	for (const auto Importer : Importers)
	{
		Importer->SetDirectory(OutFolder);
		if (!Importer->Valid())
		{
			LogWarning(FString::Printf(TEXT("Invalid Static Data found at %s"), *OutFolder));
			LogError(Importer->GetErrorReason());
			return false;
		}
	}	
	
	Ready = true;
	ImportPath = OutFolder;
	SaveConfig();
	return true;
}

bool UStaticDataImporter::IsReady()
{
	return Ready;
}

bool UStaticDataImporter::UpdateAsset(UStaticData* Asset)
{
	if (ImportPath.Len() == 0)
	{
		LogError("Import Directory not set");
		return false;
	}
	if (!IFileManager::Get().DirectoryExists(*ImportPath))
	{
		LogError("Import Directory does not exist");
		return false;
	}

	if (!IFileManager::Get().DirectoryExists(*ImportPath))
	{
		LogWarning(FString::Printf(TEXT("No Directory found at %s"), *ImportPath));
		return false;
	}

	UKismetSystemLibrary::BeginTransaction("StaticDataImporter", FText::FromString("Data Import"), Asset);
	UKismetSystemLibrary::TransactObject(Asset);

	for (const auto DataImporter : Importers)
	{
		DataImporter->SetDirectory(ImportPath);
		if (!DataImporter->Valid())
		{
			LogWarning(FString::Printf(TEXT("Invalid Static Data found at %s"), *ImportPath));
			LogError(DataImporter->GetErrorReason());
			return false;
		}
		
		if(!DataImporter->ImportAndUpdate(Asset))
		{
			LogMessage(FString::Printf(TEXT("Importer %s failed because: %s"), *DataImporter->FileName, *DataImporter->GetErrorReason()));
		}
	}

	Asset->Modify(true);
	UKismetSystemLibrary::EndTransaction();
	
	LogMessage("Import Succeeded!");

	for (const auto DataImporter : Importers)
	{
		DataImporter->Reset();
	}
	
	return true;
}

void UStaticDataImporter::LogError(const FString Text) const
{
	OnLogMessage.Broadcast(FString::Printf(TEXT("%ls\n"), *Text));
	UE_LOG(LogSupremacyEditor, Error, TEXT("%s"), *Text);
}

void UStaticDataImporter::LogWarning(const FString Text) const
{
	OnLogMessage.Broadcast(FString::Printf(TEXT("%ls\n"), *Text));
	UE_LOG(LogSupremacyEditor, Warning, TEXT("%s"), *Text);
}

void UStaticDataImporter::LogMessage(const FString Text) const
{
	OnLogMessage.Broadcast(FString::Printf(TEXT("%ls\n"), *Text));
	UE_LOG(LogSupremacyEditor, Log, TEXT("%s"), *Text);
}
