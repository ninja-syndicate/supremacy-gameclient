#pragma once

#include "CoreMinimal.h"
#include "StaticData/StaticData.h"
#include "Utils/CSVImporter.h"

class UStaticData;

namespace StaticDataImporter
{
	class Base
	{
	public:
		void SetDirectory(FString DirectoryPath);
		bool Valid();
		virtual bool ImportAndUpdate(UStaticData *DataAsset);
		FString GetErrorReason();
		virtual ~Base();

		FString FileName;
	protected:
		Base();

		bool ParseGuid(FString Field, FString Name, FGuid& ID);
		bool ParseInt(FString Field, FString Name, int32& Value);
		bool ParseFloat(FString Field, FString Name, float& Value);
		bool ParseBool(FString Field, FString Name, bool& Value);

		bool CombineGuidsUnique(const FGuid& A, const FGuid& B, FGuid &out);
		
		bool ParseColor(FString Field, FString Name, FColor& Color);

		void SetAssetName(UStaticData* DataAsset, UStaticDataBaseRecord* Record, FString Prefix) const;
		
		virtual bool HandleRow(UStaticData *DataAsset, TArray<FString> RowCells) = 0;

		FString FullPath;
		FString ErrorReason;

		TArray<FString> FileHeaders;
		Utils::CSVImporter Importer;
	};
	
}

