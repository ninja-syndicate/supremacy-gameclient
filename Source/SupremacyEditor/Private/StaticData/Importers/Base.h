#pragma once

#include "CoreMinimal.h"
#include "Utils/CSVImporter.h"

namespace StaticDataImporter
{
	class Base
	{
	public:
		void SetDirectory(FString DirectoryPath);
		bool Valid() const;
		
	protected:
		Base();
		~Base();
		FString FileName;
		TArray<FString> FileHeaders;

	private:
		FString FullPath;
		Utils::CSVImporter* Importer = nullptr;
	};
	
}

