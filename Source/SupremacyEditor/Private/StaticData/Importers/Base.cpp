#include "Base.h"
#include "SupremacyEditorModule.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


StaticDataImporter::Base::Base()
{
}

StaticDataImporter::Base::~Base()
{
}

bool StaticDataImporter::Base::ParseGuid(FString Field, FGuid& ID)
{
	if (FGuid::Parse(Field, ID)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse id on line {1}"), {
		FileName, Importer.GetCurrentIndex() + 1
	});
	return false;
}

void StaticDataImporter::Base::SetDirectory(FString DirectoryPath)
{
	FullPath = FPaths::Combine(DirectoryPath, FileName);
}

bool StaticDataImporter::Base::Valid()
{
	if (!FPaths::FileExists(FullPath))
	{
		ErrorReason = FString::Format(TEXT("Could not find file at {0}"), {FileName});
		return false;
	}
	
	if (!Importer.SetFileName(FullPath))
	{
		ErrorReason = FString::Format(TEXT("Could not initialize importer for file at {0}"), {FileName});
		return false;
	}

	TArray<FString> headers;
	if (!Importer.GetHeader(headers))
	{
		ErrorReason = FString::Format(TEXT("Could not get headers for file at {0}"), {FileName});
		return false;
	}

	if (headers.Num() != FileHeaders.Num())
	{
		ErrorReason = FString::Format(TEXT("file {0} had {1} headers, should have had {2} headers"), {
			FileName, headers.Num(), FileHeaders.Num()});
		return false;
	}

	for (int index = 0; index < headers.Num(); ++index)
	{
		if (headers[index] != FileHeaders[index])
		{
			ErrorReason = FString::Format(TEXT("file {0}'s {1} header was \"{2}\" not \"{3}\""), {
				FileName, index, headers[index], FileHeaders[index]});
			return false;
		}
	}
	return true;
}

bool StaticDataImporter::Base::ImportAndUpdate(UStaticData* DataAsset)
{
	TArray<FString> rowData;
	bool success = true;

	while(Importer.GetNextDataRow(rowData))
	{
		if (rowData.Num() != FileHeaders.Num())
		{
			success = false;
			break;
		}

		if (!HandleRow(DataAsset, rowData))
		{
			success = false;
			break;
		}
	}

	return success;
}

FString StaticDataImporter::Base::GetErrorReason()
{
	return ErrorReason;
}
