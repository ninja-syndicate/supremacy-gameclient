// Copyright 2017-2020 David Romanski(Socke). All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FJSONParserModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
