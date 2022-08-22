// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IDesktopPlatform.h"
#include "StaticDataImporter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SUPREMACYEDITOR_API UStaticDataImporter : public UObject
{
	GENERATED_BODY()

	UStaticDataImporter();
public:
	UFUNCTION(BlueprintCallable, Category = "Static Data Importer", DisplayName = "Set Import Directory", meta=(Keywords = "Set where we get the static data from"))
	bool SetImportDirectory();
	UFUNCTION(BlueprintCallable, Category = "Static Data Importer", DisplayName = "Is Ready", meta=(Keywords = "See if importer is ready to execute"))
	bool IsReady();
	
private:
	bool Ready;
	IDesktopPlatform *DesktopPlatform;
	const void *ParentWindowHandle;
};
