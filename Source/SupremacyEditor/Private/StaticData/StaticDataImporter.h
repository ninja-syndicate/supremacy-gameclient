// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IDesktopPlatform.h"
#include "EntitySystem/MovieSceneEntityBuilder.h"
#include "StaticData/StaticData.h"
#include "StaticDataImporter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddLogMessage, FString, Message);

UCLASS(Blueprintable)
class SUPREMACYEDITOR_API UStaticDataImporter : public UObject
{
	GENERATED_BODY()
public:
	UStaticDataImporter();
	virtual ~UStaticDataImporter() override;

	UPROPERTY(BlueprintAssignable)
	FAddLogMessage OnLogMessage;
	
	UFUNCTION(BlueprintCallable, Category = "Static Data", DisplayName = "Set Import Directory", meta=(Keywords = "Set where we get the static data from"))
	bool SetImportDirectory();
	UFUNCTION(BlueprintCallable, Category = "Static Data", DisplayName = "Is Ready", meta=(Keywords = "See if importer is ready to execute"))
	bool IsReady();
	UFUNCTION(BlueprintCallable, Category = "Static Data", DisplayName = "Update Asset", meta=(Keywords = "Update specified asset"))
	bool UpdateAsset(UStaticData *asset);
	
	UFUNCTION(BlueprintCallable)
	FString GetImportPath() { return ImportPath; }
	
private:
	FString ImportPath;

	TArray<StaticDataImporter::Base*> Importers;
	
	bool Ready;
	IDesktopPlatform *DesktopPlatform;
	const void *ParentWindowHandle;
	void LogError(FString text) const;
	void LogWarning(FString text) const;
	void LogMessage(FString text) const;
};
