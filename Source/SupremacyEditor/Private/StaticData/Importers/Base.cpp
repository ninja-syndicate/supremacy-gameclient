#include "Base.h"

#include "Misc/Paths.h"

void StaticDataImporter::Base::SetDirectory(FString DirectoryPath)
{
	FullPath = FPaths::Combine(DirectoryPath, FileName);
}

bool StaticDataImporter::Base::Valid() const
{
	return FPaths::FileExists(FullPath);
}
