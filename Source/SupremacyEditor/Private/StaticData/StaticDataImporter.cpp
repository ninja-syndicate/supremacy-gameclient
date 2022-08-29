// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataImporter.h"
#include "SupremacyEditorModule.h"
#include "DesktopPlatformModule.h"

UStaticDataImporter::UStaticDataImporter()
{
	FactionImporter = new StaticDataImporter::Faction();
	BrandImporter = new StaticDataImporter::Brand();

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
	delete(FactionImporter);
	delete(BrandImporter);
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

	FactionImporter->SetDirectory(outFolder);
	if (!FactionImporter->Valid())
	{
		LogWarning(FString::Printf(TEXT("Invalid Faction Static Data found at %s"), *outFolder));
		LogError(FactionImporter->GetErrorReason());
		return false;
	}

	BrandImporter->SetDirectory(outFolder);
	if (!BrandImporter->Valid())
	{
		LogWarning(FString::Printf(TEXT("Invalid Brand Static Data found at %s"), *outFolder));
		LogError(BrandImporter->GetErrorReason());
		return false;
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
	FactionImporter->ImportAndUpdate(asset);
	BrandImporter->ImportAndUpdate(asset);
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

