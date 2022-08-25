#pragma once

namespace Utils
{
	class CSVImporter
	{
	public:
		bool SetFileName(FString Filename);
		bool GetHeader(TArray<FString>& Result);
		void Reset();
		bool GetNextDataRow(TArray<FString>& Result);
		int GetCurrentIndex() const { return currentIndex; }
		
	private:
		FString CurrentFilename = "";
		TArray<FString> FileData;
		bool dataLoaded = false;
		int currentIndex = 1;
		
		static bool ParseLine(TArray<FString>& Result, FString Line);
		bool LoadData();
	};
}
