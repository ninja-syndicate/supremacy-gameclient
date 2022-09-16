// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticData/StaticData.h"

#define STATIC_DATA_STUFF_IMPL(n) \
UStaticData##n* UStaticData::Get##n(const FGuid& ID) { for (UStaticData##n* r : n##Array) { if(r->ID == ID) return r; } return nullptr; } \
UStaticData##n* UStaticData::GetOrCreate##n(const FGuid& ID) { UStaticData##n* r = Get##n(ID); if(r) return r; r = NewObject<UStaticData##n>(this); r->ID = ID; n##Array.Push(r); return r; }

STATIC_DATA_STUFF_IMPL(Faction);
STATIC_DATA_STUFF_IMPL(Brand);
STATIC_DATA_STUFF_IMPL(WarMachineModel);
STATIC_DATA_STUFF_IMPL(Skin);
STATIC_DATA_STUFF_IMPL(WeaponSkin);
STATIC_DATA_STUFF_IMPL(Weapon);
STATIC_DATA_STUFF_IMPL(MechSkinCompatibility);
STATIC_DATA_STUFF_IMPL(WeaponSkinCompatibility);
STATIC_DATA_STUFF_IMPL(PowerCore);
STATIC_DATA_STUFF_IMPL(BattleAbility);