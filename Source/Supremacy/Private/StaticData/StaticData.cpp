// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticData/StaticData.h"

UStaticDataFaction* UStaticData::GetFaction(const FGuid& ID)
{
	for (UStaticDataFaction *Faction : Factions)
	{
		if (Faction->ID == ID)
		{
			return Faction;
		}
	}

	return nullptr;
}

UStaticDataBrand* UStaticData::GetBrand(const FGuid& ID)
{
	for (UStaticDataBrand *Record : Brands)
	{
		if (Record->ID == ID)
		{
			return Record;
		}
	}

	return nullptr;
}

UStaticDataWarMachineModel* UStaticData::GetWarMachineModel(const FGuid& ID)
{
	for (UStaticDataWarMachineModel *Record : WarMachineModels)
	{
		if (Record->ID == ID)
		{
			return Record;
		}
	}

	return nullptr;
}

UStaticDataSkin* UStaticData::GetSkin(const FGuid& ID)
{
	for (UStaticDataSkin *Record : Skins)
	{
		if (Record->ID == ID)
		{
			return Record;
		}
	}

	return nullptr;
}


UStaticDataFaction* UStaticData::GetOrCreateFaction(const FGuid& ID)
{
	UStaticDataFaction* Record = GetFaction(ID);
	if (Record != nullptr) return Record;

	Record = NewObject<UStaticDataFaction>(this);
	Record->ID = ID;
	Factions.Push(Record);

	return Record;
}

UStaticDataBrand* UStaticData::GetOrCreateBrand(const FGuid& ID)
{
	UStaticDataBrand* Record = GetBrand(ID);
	if (Record != nullptr) return Record;

	Record = NewObject<UStaticDataBrand>(this);
	Record->ID = ID;
	Brands.Push(Record);

	return Record;
}

UStaticDataWarMachineModel* UStaticData::GetOrCreateWarMachineModel(const FGuid& ID)
{
	UStaticDataWarMachineModel* Record = GetWarMachineModel(ID);
	if (Record != nullptr) return Record;

	Record = NewObject<UStaticDataWarMachineModel>(this);
	Record->ID = ID;
	WarMachineModels.Push(Record);

	return Record;
}

UStaticDataSkin* UStaticData::GetOrCreateSkin(const FGuid& ID)
{
	UStaticDataSkin* Record = GetSkin(ID);
	if(Record) return Record;

	Record = NewObject<UStaticDataSkin>(this);
	Record->ID = ID;
	Skins.Push(Record);

	return Record;
}