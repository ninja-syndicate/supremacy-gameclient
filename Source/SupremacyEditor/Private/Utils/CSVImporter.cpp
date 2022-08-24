#include "CSVImporter.h"

#include "Misc/FileHelper.h"

bool Utils::CSVImporter::SetFileName(FString Filename)
{
	if (Filename == CurrentFilename) return true;
	CurrentFilename = Filename;
	return true;
}

bool Utils::CSVImporter::GetHeader(TArray<FString>& Result) const
{
	TArray<FString> fileData;
	if (!FFileHelper::LoadFileToStringArray(fileData, *CurrentFilename)) return false;

	if (fileData.Num() == 0) return false;
	return ParseLine(Result, fileData[0]);
}

bool Utils::CSVImporter::ParseLine(TArray<FString>& Result, FString Line)
{
	Result.Empty();
	bool inQuote = false;
	bool startOfField = true;
	FString currentValue;
	while(Line.Len() > 0)
	{
		TCHAR token = Line[0];
		if (token == '"')
		{
			if (startOfField)
			{
				inQuote = true;
				Line.RemoveAt(0, 1);
				continue;
			}

			if (inQuote)
			{
				inQuote = false;
				Line.RemoveAt(0, 1);
				continue;
			}
		}

		if (token == '\\' && Line.Len() > 1)
		{
			if (Line[1] == '"')
			{
				currentValue.AppendChar('\"');
				Line.RemoveAt(0, 2);
				continue;
			}

			if (Line[1] == '\\')
			{
				currentValue.AppendChar('\\');
				Line.RemoveAt(0, 2);
				continue;
			}
		}

		if (!inQuote && token == ',')
		{
			Result.Push(currentValue);
			currentValue.Empty();
			startOfField = true;
			Line.RemoveAt(0, 1);
			continue;
		}

		currentValue.AppendChar(token);
		startOfField = false;
		Line.RemoveAt(0, 1);
	}

	if (currentValue.Len() > 0) Result.Push(currentValue);

	return true;
}
