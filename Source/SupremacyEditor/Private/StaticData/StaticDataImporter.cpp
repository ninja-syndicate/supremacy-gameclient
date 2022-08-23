// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataImporter.h"
#include "SupremacyEditorModule.h"
#include "DesktopPlatformModule.h"

UStaticDataImporter::UStaticDataImporter()
{
	FactionImporter = new StaticDataImporter::Faction();
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
}

bool UStaticDataImporter::SetImportDirectory()
{
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
		LogWarning(FString::Printf(TEXT("Invalid Static Data found at %s"), *outFolder));
		return false;
	}


	ImportPath = outFolder;
	return true;
}

bool UStaticDataImporter::IsReady()
{
	return Ready;
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

