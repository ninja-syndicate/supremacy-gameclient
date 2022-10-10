// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticData/StaticData.h"

UStaticDataFaction* UStaticData::GetFaction(const FGuid& ID)
{
    for (UStaticDataFaction* Record : FactionArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find faction %s"), *ID.ToString());
    return nullptr;
}

UStaticDataBrand* UStaticData::GetBrand(const FGuid& ID)
{
    for (UStaticDataBrand* Record : BrandArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find brand %s"), *ID.ToString());
    return nullptr;
}

UStaticDataWarMachineModel* UStaticData::GetWarMachineModel(const FGuid& ID)
{
    for (UStaticDataWarMachineModel* Record : WarMachineModelArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find war machine model %s"), *ID.ToString());
    return nullptr;
}

UStaticDataSkin* UStaticData::GetSkin(const FGuid& ID)
{
    for (UStaticDataSkin* Record : SkinArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find skin %s"), *ID.ToString());
    return nullptr;
}

UStaticDataWeaponSkin* UStaticData::GetWeaponSkin(const FGuid& ID)
{
    for (UStaticDataWeaponSkin* Record : WeaponSkinArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find weapon skin %s"), *ID.ToString());
    return nullptr;
}

UStaticDataWeapon* UStaticData::GetWeapon(const FGuid& ID)
{
    for (UStaticDataWeapon* Record : WeaponArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find weapon %s"), *ID.ToString());
    return nullptr;
}

UStaticDataMechSkinCompatibility* UStaticData::GetMechSkinCompatibility(const FGuid& ID)
{
    for (UStaticDataMechSkinCompatibility* Record : MechSkinCompatibilityArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find mech skin compatibility %s"), *ID.ToString());
    return nullptr;
}

UStaticDataWeaponSkinCompatibility* UStaticData::GetWeaponSkinCompatibility(const FGuid& ID)
{
    for (UStaticDataWeaponSkinCompatibility* Record : WeaponSkinCompatibilityArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find weapon skin compatibility %s"), *ID.ToString());
    return nullptr;
}

UStaticDataPowerCore* UStaticData::GetPowerCore(const FGuid& ID)
{
    for (UStaticDataPowerCore* Record : PowerCoreArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find power core %s"), *ID.ToString());
    return nullptr;
}

UStaticDataBattleAbility* UStaticData::GetBattleAbility(const FGuid& ID)
{
    for (UStaticDataBattleAbility* Record : BattleAbilityArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find battle ability %s"), *ID.ToString());
    return nullptr;
}

UStaticDataPlayerAbility* UStaticData::GetPlayerAbility(const FGuid& ID)
{
    for (UStaticDataPlayerAbility* Record : PlayerAbilityArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find player ability %s"), *ID.ToString());
    return nullptr;
}

UStaticDataGameAbility* UStaticData::GetGameAbility(const FGuid& ID)
{
    for (UStaticDataGameAbility* Record : GameAbilityArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find game ability %s"), *ID.ToString());
    return nullptr;
}

UStaticDataShieldType* UStaticData::GetShieldType(const FGuid& ID)
{
    for (UStaticDataShieldType* Record : ShieldTypeArray) if (Record->ID == ID) return Record;
    UE_LOG(LogTemp, Error, TEXT("Failed to find shield type %s"), *ID.ToString());
    return nullptr;
}

UStaticDataFaction* UStaticData::GetOrCreateFaction(const FGuid& ID)
{
    UStaticDataFaction* Record = GetFaction(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataFaction>(this);
    Record->ID = ID;
    FactionArray.Push(Record);

    return Record;
}

UStaticDataBrand* UStaticData::GetOrCreateBrand(const FGuid& ID)
{
    UStaticDataBrand* Record = GetBrand(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataBrand>(this);
    Record->ID = ID;
    BrandArray.Push(Record);

    return Record;
}

UStaticDataWarMachineModel* UStaticData::GetOrCreateWarMachineModel(const FGuid& ID)
{
    UStaticDataWarMachineModel* Record = GetWarMachineModel(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataWarMachineModel>(this);
    Record->ID = ID;
    WarMachineModelArray.Push(Record);

    return Record;
}

UStaticDataSkin* UStaticData::GetOrCreateSkin(const FGuid& ID)
{
    UStaticDataSkin* Record = GetSkin(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataSkin>(this);
    Record->ID = ID;
    SkinArray.Push(Record);

    return Record;
}

UStaticDataWeaponSkin* UStaticData::GetOrCreateWeaponSkin(const FGuid& ID)
{
    UStaticDataWeaponSkin* Record = GetWeaponSkin(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataWeaponSkin>(this);
    Record->ID = ID;
    WeaponSkinArray.Push(Record);

    return Record;
}

UStaticDataWeapon* UStaticData::GetOrCreateWeapon(const FGuid& ID)
{
    UStaticDataWeapon* Record = GetWeapon(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataWeapon>(this);
    Record->ID = ID;
    WeaponArray.Push(Record);

    return Record;
}

UStaticDataMechSkinCompatibility* UStaticData::GetOrCreateMechSkinCompatibility(const FGuid& ID)
{
    UStaticDataMechSkinCompatibility* Record = GetMechSkinCompatibility(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataMechSkinCompatibility>(this);
    Record->ID = ID;
    MechSkinCompatibilityArray.Push(Record);

    return Record;
}

UStaticDataWeaponSkinCompatibility* UStaticData::GetOrCreateWeaponSkinCompatibility(const FGuid& ID)
{
    UStaticDataWeaponSkinCompatibility* Record = GetWeaponSkinCompatibility(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataWeaponSkinCompatibility>(this);
    Record->ID = ID;
    WeaponSkinCompatibilityArray.Push(Record);

    return Record;
}

UStaticDataPowerCore* UStaticData::GetOrCreatePowerCore(const FGuid& ID)
{
    UStaticDataPowerCore* Record = GetPowerCore(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataPowerCore>(this);
    Record->ID = ID;
    PowerCoreArray.Push(Record);

    return Record;
}

UStaticDataBattleAbility* UStaticData::GetOrCreateBattleAbility(const FGuid& ID)
{
    UStaticDataBattleAbility* Record = GetBattleAbility(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataBattleAbility>(this);
    Record->ID = ID;
    BattleAbilityArray.Push(Record);

    return Record;
}

UStaticDataPlayerAbility* UStaticData::GetOrCreatePlayerAbility(const FGuid& ID)
{
    UStaticDataPlayerAbility* Record = GetPlayerAbility(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataPlayerAbility>(this);
    Record->ID = ID;
    PlayerAbilityArray.Push(Record);

    return Record;
}

UStaticDataGameAbility* UStaticData::GetOrCreateGameAbility(const FGuid& ID)
{
    UStaticDataGameAbility* Record = GetGameAbility(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataGameAbility>(this);
    Record->ID = ID;
    GameAbilityArray.Push(Record);

    return Record;
}

UStaticDataShieldType* UStaticData::GetOrCreateShieldType(const FGuid& ID)
{
    UStaticDataShieldType* Record = GetShieldType(ID);
    if (Record) return Record;

    Record = NewObject<UStaticDataShieldType>(this);
    Record->ID = ID;
    ShieldTypeArray.Push(Record);

    return Record;
}

FFaction UStaticData::FactionFromStaticDataFaction(const FGuid& ID)
{
    UStaticDataFaction* Faction = GetFaction(ID);

    FFaction Out;

    Out.ID = Faction->ID.ToString();
    Out.Name = Faction->Label;
    Out.Color = Faction->PrimaryColor;

    return Out;
}

UFUNCTION(BlueprintCallable)
FWeaponStruct UStaticData::WeaponStruct(const FGuid& WeaponID) {
    FWeaponStruct Struct;

    UStaticDataWeapon* Record = GetWeapon(WeaponID);
    if (!Record) {
        UE_LOG(LogTemp, Warning, TEXT("failed to find weapon with id %s"), *WeaponID.ToString());
        return Struct;
    }

    Struct.Damage = Record->Damage;
    Struct.Damage_Falloff = Record->DamageFalloff;
    Struct.Damage_Falloff_Rate = Record->DamageFalloffRate;
    Struct.Damage_Radius = Record->Radius;
    Struct.Damage_Radius_Falloff = Record->RadiusDamageFalloff;
    Struct.Damage_Type = (uint8)Record->WeaponDamageType;
    Struct.Spread = Record->Spread;
    Struct.Rate_Of_Fire = Record->RateOfFire;
    Struct.Burst_Rate_Of_Fire = Record->BurstRateOfFire;
    Struct.Projectile_Speed = Record->ProjectileSpeed;
    Struct.Max_Ammo = Record->MaxAmmo;
    Struct.Projectile_Amount = Record->ProjectileAmount;
    //Struct.Projectile_Life_Span = ...;
    Struct.Charge_Time = Record->ChargeTimeSeconds;
    Struct.Is_Arced = Record->IsArced;
    //Struct.Optimal_Range = ...;
    //Struct.Recoil_Force = ...;
    Struct.Power_Cost = Record->EnergyCost;
    Struct.Power_Instance_Drain = Record->PowerInstantDrain;

    return Struct;
}

UFUNCTION(BlueprintCallable)
FPowerCoreStruct UStaticData::PowerCoreStruct(const FGuid& PowerCoreID) {
    FPowerCoreStruct Struct;

    UStaticDataPowerCore* Record = GetPowerCore(PowerCoreID);
    if (!Record) {
        UE_LOG(LogTemp, Warning, TEXT("failed to find power core with id %s"), *PowerCoreID.ToString());
        return Struct;
    }

    Struct.Max_Draw_Rate = Record->MaxDrawRate;
    Struct.Power_Capacity = Record->Capacity;
    Struct.Recharge_Rate = Record->RechargeRate;

    return Struct;
}

FWarMachineStruct UStaticData::WarMachineStruct(const FGuid& MechID) 
{
    UStaticDataWarMachineModel* WarMachine = GetWarMachineModel(MechID);

    FWarMachineStruct Out;
    if (!WarMachine) 
    {
        UE_LOG(LogTemp, Error, TEXT("WarMachineStructFromStaticDataWarMachine: bad war machine ID (%s)"), *(MechID.ToString()));
        return Out;
    }
   
    Out.Name = WarMachine->Label;
    Out.Faction = FactionFromStaticDataFaction(WarMachine->Brand->Faction->ID);

    //ERarity Rarity;

    Out.Health = WarMachine->MaxHitpoints;
    Out.HealthMax = WarMachine->MaxHitpoints;
    Out.ShieldMax = WarMachine->MaxShield;
    Out.ShieldRechargeRate = WarMachine->ShieldRechargeRate;
    Out.Speed = WarMachine->Speed;

    return Out;
}

static bool CombineGuidsUnique(const FGuid& A, const FGuid& B, FGuid& Out)
{
    uint8 Buffer[16] = { 0 };
    FString AString = A.ToString();
    FString BString = B.ToString();

    for (int32 i = 0; i < 16;)
    {
        if (AString[i] == '-')
        {
            continue;
        }

        Buffer[i] = (unsigned char)AString[i] ^ (unsigned char)BString[i];
        i++;
    }

    int32 i0 = Buffer[0] + (Buffer[1] << 8) + (Buffer[2] << 16) + (Buffer[3] << 24);
    int32 i1 = Buffer[4] + (Buffer[5] << 8) + (Buffer[6] << 16) + (Buffer[7] << 24);
    int32 i2 = Buffer[8] + (Buffer[9] << 8) + (Buffer[10] << 16) + (Buffer[11] << 24);
    int32 i3 = Buffer[12] + (Buffer[13] << 8) + (Buffer[14] << 16) + (Buffer[15] << 24);

    Out = FGuid(i0, i1, i2, i3);
    return true;
}

UFUNCTION(BlueprintCallable)
TMap<FString, TSoftObjectPtr<UMaterial>> UStaticData::MaterialsForMech(const FGuid& MechID, const FGuid& SkinID) {
    FGuid ID;
    CombineGuidsUnique(MechID, SkinID, ID);
    UStaticDataMechSkinCompatibility* Record = GetMechSkinCompatibility(ID);
    if (Record) return Record->Materials;
    return TMap<FString, TSoftObjectPtr<UMaterial>>();
}

UFUNCTION(BlueprintCallable)
TMap<FString, TSoftObjectPtr<UMaterial>> UStaticData::MaterialsForWeapon(const FGuid& WeaponID, const FGuid& SkinID) {
    FGuid ID;
    CombineGuidsUnique(WeaponID, SkinID, ID);
    UStaticDataWeaponSkinCompatibility* Record = GetWeaponSkinCompatibility(ID);
    if(Record) return Record->Materials;
    return TMap<FString, TSoftObjectPtr<UMaterial>>();
}