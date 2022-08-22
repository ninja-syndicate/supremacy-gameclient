// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticDataImporter.h"
#include "SupremacyEditorModule.h"
#include "DesktopPlatformModule.h"

UStaticDataImporter::UStaticDataImporter()
{
	DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform == nullptr)
	{
		UE_LOG(LogSupremacyEditor, Error, TEXT("Unable to load desktop platform! This is a fatal error!"))
		return;
	}
}

bool UStaticDataImporter::SetImportDirectory()
{
	if (DesktopPlatform == nullptr)
	{
		UE_LOG(LogSupremacyEditor, Error, TEXT("Unable to load desktop platform! Can't set import directory"));
		return false;
	}

	FString outFolder;
	if (!DesktopPlatform->OpenDirectoryDialog(nullptr, "Select Static Directory", "..", outFolder))
	{
		UE_LOG(LogSupremacyEditor, Log, TEXT("No Folder selected"));
		return false;
	}

	
	
	return true;
}

bool UStaticDataImporter::IsReady()
{
	return Ready;
}

