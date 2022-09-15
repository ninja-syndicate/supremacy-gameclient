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

UStaticDataWeapon *UStaticData::GetWeapon(const FGuid& ID)
{
	for (UStaticDataWeapon *Record : Weapons)
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

UStaticDataWeaponSkin* UStaticData::GetWeaponSkin(const FGuid& ID)
{
	for (UStaticDataWeaponSkin *Record : WeaponSkins)
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

UStaticDataWeaponSkin* UStaticData::GetOrCreateWeaponSkin(const FGuid& ID)
{
	UStaticDataWeaponSkin* Record = GetWeaponSkin(ID);
	if(Record) return Record;

	Record = NewObject<UStaticDataWeaponSkin>(this);
	Record->ID = ID;
	WeaponSkins.Push(Record);

	return Record;
}

UStaticDataWeapon* UStaticData::GetOrCreateWeapon(const FGuid& ID)
{
	UStaticDataWeapon* Record = GetWeapon(ID);
	if(Record) return Record;

	Record = NewObject<UStaticDataWeapon>(this);
	Record->ID = ID;
	Weapons.Push(Record);
	
	return Record;
}

UStaticDataMechSkinCompatibility *UStaticData::GetOrCreateMechSkinCompatibility(const FGuid& ID)
{
	UStaticDataMechSkinCompatibility* Record = GetMechSkinCompatibility(ID);
	if(Record) return Record;

	Record = NewObject<UStaticDataMechSkinCompatibility>(this);
	Record->ID = ID;
	MechSkinCompatibilities.Push(Record);
	
	return Record;
}

UStaticDataWeaponSkinCompatibility *UStaticData::GetOrCreateWeaponSkinCompatibility(const FGuid& ID)
{
	UStaticDataWeaponSkinCompatibility* Record = GetWeaponSkinCompatibility(ID);
	if(Record) return Record;

	Record = NewObject<UStaticDataWeaponSkinCompatibility>(this);
	Record->ID = ID;
	WeaponSkinCompatibilities.Push(Record);
	
	return Record;
}

UStaticDataMechSkinCompatibility* UStaticData::GetMechSkinCompatibility(const FGuid& ID)
{
	for (UStaticDataMechSkinCompatibility *Record : MechSkinCompatibilities)
	{
		if (Record->ID == ID)
		{
			return Record;
		}
	}

	return nullptr;
}

UStaticDataWeaponSkinCompatibility* UStaticData::GetWeaponSkinCompatibility(const FGuid& ID)
{
	for (UStaticDataWeaponSkinCompatibility *Record : WeaponSkinCompatibilities)
	{
		if (Record->ID == ID)
		{
			return Record;
		}
	}

	return nullptr;
}
