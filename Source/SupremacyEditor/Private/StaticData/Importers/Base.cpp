﻿#include "Base.h"
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
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2} (got {3})"), {
		FileName, Name, Importer.GetCurrentIndex() + 1, Field
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

	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2} (got {3})"), {
		FileName, Name, Importer.GetCurrentIndex() + 1, Field
	});

	return false;
}

bool StaticDataImporter::Base::ParseInt(FString Field, FString Name, int32& Value)
{
	if(FDefaultValueHelper::ParseInt(Field, Value)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2} (got {3})"), {
		FileName, Name, Importer.GetCurrentIndex() + 1, Field
	});
	return false;
}

bool StaticDataImporter::Base::ParseFloat(FString Field, FString Name, float& Value)
{
	if(FDefaultValueHelper::ParseFloat(Field, Value)) return true;
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2} (got {3})"), {
		FileName, Name, Importer.GetCurrentIndex() + 1, Field
	});
	return false;
}

bool StaticDataImporter::Base::ParseBool(FString Field, FString Name, bool& Value)
{
	if(Field.ToLower() == "true")
	{
		Value = true;
		return true;
	}
	
	if(Field.ToLower() == "false")
	{
		Value = false;
		return true;
	}
	
	ErrorReason = FString::Format(TEXT("{0} - unable to parse {1} on line {2} (got {3})"), {
			FileName, Name, Importer.GetCurrentIndex() + 1, Field
	});
	
	return false;
}

void StaticDataImporter::Base::SetAssetName(UStaticData* DataAsset, UStaticDataBaseRecord* Record, FString Prefix) const
{
	const FString AssetName = FString::Format(TEXT("{0} - {1}"), { Prefix, Record->Label });

	// use the REN_Test flag to test if the renaming will succeed, otherwise, if a record with the
	// same name already exists, a breakpoint (or crash) will occur
	if(Record->Rename(*AssetName, DataAsset, REN_Test))
	{
		Record->Rename(*AssetName, DataAsset);
	}
	else
	{
		// We likely have a name conflict. Try adding a number to the end.
		int32 i = 1;
		while(true)
		{
			FString Name = AssetName + FString::FromInt(i);
			if(Record->Rename(*Name, DataAsset, REN_Test))
			{
				Record->Rename(*Name, DataAsset);
				break;
			}

			i += 1;

			// Ensure we don't infinite loop if we can't find a name that will succeed.
			if(i >= 16) break;
		}
	}
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

	TArray<FString> Headers;
	if (!Importer.GetHeader(Headers))
	{
		ErrorReason = FString::Format(TEXT("Could not get headers for file at {0}"), {FileName});
		return false;
	}

	if (Headers.Num() != FileHeaders.Num())
	{
		ErrorReason = FString::Format(TEXT("file {0} had {1} headers, should have had {2} headers"), {
			FileName, Headers.Num(), FileHeaders.Num()});
		return false;
	}

	for (int Index = 0; Index < Headers.Num(); ++Index)
	{
		if (Headers[Index] != FileHeaders[Index])
		{
			ErrorReason = FString::Format(TEXT("file {0}'s {1} header was \"{2}\" not \"{3}\""), {
				FileName, Index, Headers[Index], FileHeaders[Index]});
			return false;
		}
	}
	return true;
}

bool StaticDataImporter::Base::ImportAndUpdate(UStaticData* DataAsset)
{
	TArray<FString> RowData;
	bool bSuccess = true;

	while(Importer.GetNextDataRow(RowData))
	{
		if (RowData.Num() != FileHeaders.Num())
		{
			ErrorReason = FString::Printf(TEXT("header count doesn't match (line = %d, expected = %d, got = %d"), Importer.GetLineNumber(), FileHeaders.Num(), RowData.Num());
			//bSuccess = false;
			continue;
		}

		if (!HandleRow(DataAsset, RowData))
		{
			const FString Temp = ErrorReason;
			ErrorReason = FString::Printf(TEXT("failed to handle row: %s"), *Temp);
			bSuccess = false;
			break;
		}
	}

	return bSuccess;
}

void StaticDataImporter::Base::Reset()
{
	Importer.Reset();
}

FString StaticDataImporter::Base::GetErrorReason()
{
	return ErrorReason;
}

bool StaticDataImporter::Base::CombineGuidsUnique(const FGuid& A, const FGuid& B, FGuid &Out)
{
	uint8 Buffer[16] = { 0 };
	FString AString = A.ToString();
	FString BString = B.ToString();

	for(int32 i = 0; i < 16;)
	{
		if(AString[i] == '-')
		{
			continue;
		}
		
		Buffer[i] = (unsigned char)AString[i] ^ (unsigned char)BString[i];
		i++;
	}

	int32 i0 = Buffer[0] + (Buffer[1] << 8) + (Buffer[2] << 16) + (Buffer[3] << 24);
	int32 i1 = Buffer[4] + (Buffer[5] << 8) + (Buffer[6] << 16) + (Buffer[7] << 24);
	int32 i2 = Buffer[8] + (Buffer[9] << 8) + (Buffer[10] << 16) + (Buffer[11] << 24);
	int32 i3 = Buffer[12] + (Buffer[13] << 8) + (Buffer[14] << 16) + (Buffer[15] << 24);
	
	Out = FGuid(i0, i1, i2, i3);
	return true;
}