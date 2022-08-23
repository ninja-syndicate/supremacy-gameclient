#pragma once

#include "CoreMinimal.h"

namespace StaticDataImporter
{
	class Base
	{
	public:
		void SetDirectory(FString DirectoryPath);
		bool Valid() const;
		
	protected:
		FString FileName;

	private:
		FString FullPath;
	};
	
}

