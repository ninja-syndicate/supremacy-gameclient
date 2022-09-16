# Wrote this because so to avoid manually writing the same code for each type.
#
# Originally I wanted to do something like this using macros in the C++
# code, but the Unreal Header Tool would not be able to find it's metadata
# before the pre-processor expanded the macros.
#
# This will generate the function headers and implementations for each type,
# then prints it out to the command line for copy+pasting. The function
# headers go into StaticData.h, and the implementations go into StaticData.cpp.

types = [
    "Faction",
    "Brand",
    "WarMachineModel",
    "Skin",
    "WeaponSkin",
    "Weapon",
    "MechSkinCompatibility",
    "WeaponSkinCompatibility",
    "PowerCore",
    "BattleAbility",
    "PlayerAbility",
    "GameAbility"
]

for data_type in types:
    print("    friend StaticDataImporter::%s;" % data_type)
print("")
print("public:")
for data_type in types:
    print("    UFUNCTION(BlueprintCallable)")
    print("    UStaticData%s* Get%s(const FGuid& ID);\n" % (data_type, data_type))
print("private:")
for data_type in types:
    print("    UStaticData%s* GetOrCreate%s(const FGuid& ID);" % (data_type, data_type))
print("")
for data_type in types:
    print("    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))")
    print("    TArray<UStaticData%s*> %sArray;\n" % (data_type, data_type))

print("\n---------------------------------------\n")

format1 = """UStaticData%s* UStaticData::Get%s(const FGuid& ID)
{
    for (UStaticData%s* Record : %sArray) if(Record->ID == ID) return Record;
    return nullptr;
}\n"""
format2 = """UStaticData%s* UStaticData::GetOrCreate%s(const FGuid& ID)
{
    UStaticData%s* Record = Get%s(ID);
    if(Record) return Record;

    Record = NewObject<UStaticData%s>(this);
    Record->ID = ID;
    %sArray.Push(Record);

    return Record;
}\n"""

for data_type in types:
    print(format1 % (data_type, data_type, data_type, data_type))
for data_type in types:
    print(format2 % (data_type, data_type, data_type, data_type, data_type, data_type))
