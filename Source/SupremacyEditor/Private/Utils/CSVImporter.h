#pragma once

namespace Utils
{
	class CSVImporter
	{
	public:
		bool SetFileName(FString Filename);
		bool GetHeader(TArray<FString>& Result) const;
	private:
		FString CurrentFilename = "";

		static bool ParseLine(TArray<FString>& Result, FString Line);
	};
}
