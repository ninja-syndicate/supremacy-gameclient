#include "Base.h"
#include "SupremacyEditorModule.h"
#include "Misc/DefaultValueHelper.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


StaticDataImporter::Base::Base()
{
}

StaticDataImporter::Base::~Base()
{
}

bool StaticDataImporter::Base::ParseGuid(FString Field, FString Name, FGuid& ID)
{
	if (FGuid::Parse(Field, ID)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2}"), {
		FileName, Name, Importer.GetCurrentIndex() + 1
	});
	return false;
}

bool StaticDataImporter::Base::ParseColor(FString Field, FString Name, FColor& Color)
{
	//Note: this parsing was cribbed from unreal's FColor::FromHex code.
	int32 StartIndex = (!Field.IsEmpty() && Field[0] == TCHAR('#')) ? 1 : 0;

	if (Field.Len() == 3 + StartIndex)
	{
		const int32 R = FParse::HexDigit(Field[StartIndex++]);
		const int32 G = FParse::HexDigit(Field[StartIndex++]);
		const int32 B = FParse::HexDigit(Field[StartIndex]);

		Color = FColor((uint8)((R << 4) + R), (uint8)((G << 4) + G), (uint8)((B << 4) + B), 255);
		
		return true;
	}

	if (Field.Len() == 6 + StartIndex)
	{
		Color.R = (uint8)((FParse::HexDigit(Field[StartIndex+0]) << 4) + FParse::HexDigit(Field[StartIndex+1]));
		Color.G = (uint8)((FParse::HexDigit(Field[StartIndex+2]) << 4) + FParse::HexDigit(Field[StartIndex+3]));
		Color.B = (uint8)((FParse::HexDigit(Field[StartIndex+4]) << 4) + FParse::HexDigit(Field[StartIndex+5]));
		Color.A = 255;

		return true;
	}

	if (Field.Len() == 8 + StartIndex)
	{
		Color.R = (uint8)((FParse::HexDigit(Field[StartIndex+0]) << 4) + FParse::HexDigit(Field[StartIndex+1]));
		Color.G = (uint8)((FParse::HexDigit(Field[StartIndex+2]) << 4) + FParse::HexDigit(Field[StartIndex+3]));
		Color.B = (uint8)((FParse::HexDigit(Field[StartIndex+4]) << 4) + FParse::HexDigit(Field[StartIndex+5]));
		Color.A = (uint8)((FParse::HexDigit(Field[StartIndex+6]) << 4) + FParse::HexDigit(Field[StartIndex+7]));

		return true;
	}

	return false;
}

bool StaticDataImporter::Base::ParseInt(FString Field, FString Name, int32& Value)
{
	if(FDefaultValueHelper::ParseInt(Field, Value)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2}"), {
		FileName, Name, Importer.GetCurrentIndex() + 1
	});
	return false;
}

bool StaticDataImporter::Base::ParseFloat(FString Field, FString Name, float& Value)
{
	if(FDefaultValueHelper::ParseFloat(Field, Value)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2}"), {
		FileName, Name, Importer.GetCurrentIndex() + 1
	});
	return false;
}

bool StaticDataImporter::Base::ParseBool(FString Field, FString Name, bool& Value)
{
	if(Name.ToLower() == "true")
	{
		Value = true;
		return true;
	}
	
	if(Name.ToLower() == "false")
	{
		Value = false;
		return true;
	}
	
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2}"), {
			FileName, Name, Importer.GetCurrentIndex() + 1
	});
	
	return false;
}

void StaticDataImporter::Base::SetAssetName(UStaticData* DataAsset, UStaticDataBaseRecord* Record, FString Prefix) const
{
	const FString AssetName = FString::Format(TEXT("{0} - {1}"), {Prefix, Record->Label});
	Record->Rename(*AssetName, DataAsset);
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
