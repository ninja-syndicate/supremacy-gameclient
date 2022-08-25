// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticData/StaticData.h"

FStaticDataFaction UStaticData::GetOrCreateFaction(FGuid& id)
{
	for (FStaticDataFaction Faction : Factions)
	{
		if (Faction.ID == id)
		{
			return Faction;
		}
	}

	FStaticDataFaction Faction;
	Faction.ID = id;
	Factions.Push(Faction);
	return Faction;
}

void UStaticData::UpdateFaction(const FStaticDataFaction& Record)
{
	int index = -1;
	bool found = false;
	for (FStaticDataFaction Faction : Factions)
	{
		index++;
		if (Faction.ID == Record.ID)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		Factions.Push(Record);
		return;
	}

	Factions.RemoveAt(index);
	Factions.Insert(Record, index);
}
