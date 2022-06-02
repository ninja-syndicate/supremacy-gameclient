// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FGuidFixerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void FixMaterialGuids() const;
	void FixTextureGuids() const;
	void FixEmptyTextureGuids() const;
	
	
private:
	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> FixMaterialGuidsCommands;
	TSharedPtr<class FUICommandList> FixTextureGuidsCommands;
	TSharedPtr<class FUICommandList> FixEmptyTextureGuidsCommands;
};
