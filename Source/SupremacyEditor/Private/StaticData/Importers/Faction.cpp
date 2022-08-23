#include "Faction.h"

#define FILE_NAME "factions.csv"

StaticDataImporter::Faction::Faction(): Base()
{
	this->FileName = FILE_NAME;
}
