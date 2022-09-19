// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataImporter.h"
#include "SupremacyEditorModule.h"
#include "DesktopPlatformModule.h"
#include "Importers/BattleAbility.h"

#include "Importers/Faction.h"
#include "Importers/Brand.h"
#include "Importers/MechSkinCompatibility.h"
#include "Importers/PowerCore.h"
#include "Importers/WeaponSkinCompatibility.h"
#include "Importers/WarMachineModel.h"
#include "Importers/Skin.h"
#include "Importers/Weapon.h"
#include "Importers/WeaponSkin.h"
#include "Importers/BattleAbility.h"
#include "Importers/GameAbility.h"
#include "Importers/PlayerAbility.h"
#include "Importers/ShieldType.h"

UStaticDataImporter::UStaticDataImporter()
{
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

	FString outFolder;
	if (!DesktopPlatform->OpenDirectoryDialog(nullptr, "Select Static Directory", "..", outFolder))
	{
		LogWarning("No Folder selected");
		return false;
	}

	if (!IFileManager::Get().DirectoryExists(*outFolder))
	{
		LogWarning(FString::Printf(TEXT("No Directory found at %s"), *outFolder));
		return false;
	}

	for (const auto Importer : Importers)
	{
		Importer->SetDirectory(outFolder);
		if (!Importer->Valid())
		{
			LogWarning(FString::Printf(TEXT("Invalid Static Data found at %s"), *outFolder));
			LogError(Importer->GetErrorReason());
			return false;
		}
	}	
	
	Ready = true;
	ImportPath = outFolder;
	return true;
}

bool UStaticDataImporter::IsReady()
{
	return Ready;
}

bool UStaticDataImporter::UpdateAsset(UStaticData* asset)
{
	if (ImportPath.Len() == 0)
	{
		LogError("Import Directory not set");
		return false;
	}

	if (!IFileManager::Get().DirectoryExists(*ImportPath))
	{
		LogWarning(FString::Printf(TEXT("No Directory found at %s"), *ImportPath));
		return false;
	}

	UKismetSystemLibrary::BeginTransaction("StaticDataImporter", FText::FromString("Data Import"), asset);
	UKismetSystemLibrary::TransactObject(asset);

	for (const auto DataImporter : Importers)
	{
		if(!DataImporter->ImportAndUpdate(asset))
		{
			LogMessage(FString::Printf(TEXT("Importer %s failed because: %s"), *DataImporter->FileName, *DataImporter->GetErrorReason()));
		}
	}

	asset->Modify(true);
	UKismetSystemLibrary::EndTransaction();
	
	LogMessage("Import Succeeded!");
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

