#pragma once

#include "CoreMinimal.h"
#include "StaticData/StaticData.h"
#include "Utils/CSVImporter.h"

namespace StaticDataImporter
{
	class Base
	{
	public:
		void SetDirectory(FString DirectoryPath);
		bool Valid();
		virtual bool ImportAndUpdate(UStaticData *DataAsset);
		FString GetErrorReason();
		
	protected:
		Base();
		~Base();

		virtual bool HandleRow(UStaticData *DataAsset, TArray<FString> RowCells) = 0;

		FString FullPath;
		FString FileName;
		FString ErrorReason;

		TArray<FString> FileHeaders;
		Utils::CSVImporter Importer;
	};
	
}

