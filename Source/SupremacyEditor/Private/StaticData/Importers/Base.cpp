#include "Base.h"
#include "SupremacyEditorModule.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


StaticDataImporter::Base::Base()
{
	Importer = new Utils::CSVImporter();
}

StaticDataImporter::Base::~Base()
{
	if (Importer != nullptr) delete(Importer);
}

void StaticDataImporter::Base::SetDirectory(FString DirectoryPath)
{
	FullPath = FPaths::Combine(DirectoryPath, FileName);
}

bool StaticDataImporter::Base::Valid() const
{
	if (!FPaths::FileExists(FullPath)) return false;
	if (!Importer->SetFileName(FullPath)) return false;

	TArray<FString> headers;
	if (!Importer->GetHeader(headers)) return false;

	if (headers.Num() != FileHeaders.Num()) return false;

	for (int index = 0; index < headers.Num(); ++index)
	{
		if (headers[index] != FileHeaders[index]) return false;	
	}
	return true;
}
