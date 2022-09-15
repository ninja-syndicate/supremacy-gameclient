#include "CSVImporter.h"

#include "Misc/FileHelper.h"

bool Utils::CSVImporter::SetFileName(FString Filename)
{
	if (Filename == CurrentFilename) return true;
	dataLoaded = false;
	CurrentFilename = Filename;
	return true;
}

bool Utils::CSVImporter::GetHeader(TArray<FString>& Result)
{
	if (!LoadData()) return false;

	if (FileData.Num() == 0) return false;
	return ParseLine(Result, FileData[0]);
}

void Utils::CSVImporter::Reset()
{
	currentIndex = 1;
}

bool Utils::CSVImporter::GetNextDataRow(TArray<FString>& Result)
{
	if (!LoadData()) return false;
	if (currentIndex >= FileData.Num()) return false;

	const bool result = ParseLine(Result, FileData[currentIndex]);
	if (result) currentIndex++;
	return result;
}

bool Utils::CSVImporter::ParseLine(TArray<FString>& Result, FString Line)
{
	Result.Empty();
	bool inQuote = false;
	bool startOfField = true;
	FString currentValue;
	
	bool AppendEmptyField = Line[Line.Len() - 1] == ',';
	
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

	if(AppendEmptyField) Result.Push("");
	
	return true;
}

bool Utils::CSVImporter::LoadData()
{
	if (dataLoaded) return true;
	
	if (!FFileHelper::LoadFileToStringArray(FileData, *CurrentFilename))
	{
		return false;
	}
	
	dataLoaded = true;
	return true;
}
