#include "Faction.h"

StaticDataImporter::Faction::Faction(): Base()
{
	this->FileName = "factions.csv";
	this->FileHeaders = {   
		"id",
		"vote_price",
		"contract_reward",
		"label",
		"guild_id",
		"deleted_at",
		"updated_at",
		"created_at",
		"primary_color",
		"secondary_color",
		"background_color",
		"logo_url",
		"background_url",
		"description",
	};
}
