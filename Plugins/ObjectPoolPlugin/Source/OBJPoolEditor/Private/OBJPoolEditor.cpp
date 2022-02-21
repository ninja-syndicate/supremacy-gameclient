//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OBJPoolEditor.h"
#include "OBJPoolEditor_Shared.h"
#include "Kismet2/KismetEditorUtilities.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOCTEXT_NAMESPACE "Synaptech"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UOBJPoolFactory::UOBJPoolFactory(const class FObjectInitializer &OBJ) : Super(OBJ) {
	SupportedClass = UObjectPool::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UOBJPoolFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	check(Class->IsChildOf(UObjectPool::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class,InParent,Name,BPTYPE_Normal,UBlueprint::StaticClass(),UBlueprintGeneratedClass::StaticClass(),TEXT("AssetTypeActions"));
}

FText FATA_OBJP::GetAssetDescription(const FAssetData &AssetData) const {
	return FText::FromString(FString(TEXT("Blueprintable Object-Pool Component.")));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UPWPoolFactory::UPWPoolFactory(const class FObjectInitializer &OBJ) : Super(OBJ) {
	SupportedClass = UPawnPool::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UPWPoolFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	check(Class->IsChildOf(UPawnPool::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class,InParent,Name,BPTYPE_Normal,UBlueprint::StaticClass(),UBlueprintGeneratedClass::StaticClass(),TEXT("AssetTypeActions"));
}

FText FATA_PWP::GetAssetDescription(const FAssetData &AssetData) const {
	return FText::FromString(FString(TEXT("Blueprintable Pawn Object-Pool Component.")));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCHPoolFactory::UCHPoolFactory(const class FObjectInitializer &OBJ) : Super(OBJ) {
	SupportedClass = UCharacterPool::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UCHPoolFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	check(Class->IsChildOf(UCharacterPool::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class,InParent,Name,BPTYPE_Normal,UBlueprint::StaticClass(),UBlueprintGeneratedClass::StaticClass(),TEXT("AssetTypeActions"));
}

FText FATA_CHP::GetAssetDescription(const FAssetData &AssetData) const {
	return FText::FromString(FString(TEXT("Blueprintable Character Object-Pool Component.")));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

USHPoolFactory::USHPoolFactory(const class FObjectInitializer &OBJ) : Super(OBJ) {
	SupportedClass = USharedObjectPool::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* USHPoolFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
	check(Class->IsChildOf(USharedObjectPool::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class,InParent,Name,BPTYPE_Normal,UBlueprint::StaticClass(),UBlueprintGeneratedClass::StaticClass(),TEXT("AssetTypeActions"));
}

FText FATA_SHP::GetAssetDescription(const FAssetData &AssetData) const {
	return FText::FromString(FString(TEXT("Blueprintable Shared-Pool Component.")));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////