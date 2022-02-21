/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "OBJPool.h"
#include "AssetTypeActions_Base.h"
#include "Editor/UnrealEd/Classes/Factories/Factory.h"

#include "OBJPoolEditor.generated.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOCTEXT_NAMESPACE "Synaptech"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class OBJPOOLEDITOR_API UOBJPoolFactory : public UFactory {
	GENERATED_UCLASS_BODY()
protected:
	virtual bool IsMacroFactory() const { return false; }
public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class OBJPOOLEDITOR_API UPWPoolFactory : public UFactory {
	GENERATED_UCLASS_BODY()
protected:
	virtual bool IsMacroFactory() const { return false; }
public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class OBJPOOLEDITOR_API UCHPoolFactory : public UFactory {
	GENERATED_UCLASS_BODY()
protected:
	virtual bool IsMacroFactory() const { return false; }
public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class OBJPOOLEDITOR_API USHPoolFactory : public UFactory {
	GENERATED_UCLASS_BODY()
protected:
	virtual bool IsMacroFactory() const { return false; }
public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static EAssetTypeCategories::Type SY_AssetCategory;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FATA_OBJP : public FAssetTypeActions_Base {
public:
	virtual uint32 GetCategories() override { return SY_AssetCategory; }
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions","FATA_OBJP","Object Pool"); }
	virtual UClass* GetSupportedClass() const override { return UObjectPool::StaticClass(); }
	virtual FColor GetTypeColor() const override { return FColor(27,190,27); }
	//
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override;
};

class FATA_PWP : public FAssetTypeActions_Base {
public:
	virtual uint32 GetCategories() override { return SY_AssetCategory; }
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions","FATA_PWP","Pawn Pool"); }
	virtual UClass* GetSupportedClass() const override { return UPawnPool::StaticClass(); }
	virtual FColor GetTypeColor() const override { return FColor(190,27,27); }
	//
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override;
};

class FATA_CHP : public FAssetTypeActions_Base {
public:
	virtual uint32 GetCategories() override { return SY_AssetCategory; }
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions","FATA_CHP","Character Pool"); }
	virtual UClass* GetSupportedClass() const override { return UCharacterPool::StaticClass(); }
	virtual FColor GetTypeColor() const override { return FColor(27,27,190); }
	//
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override;
};

class FATA_SHP : public FAssetTypeActions_Base {
public:
	virtual uint32 GetCategories() override { return SY_AssetCategory; }
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions","FATA_SHP","Shared Pool"); }
	virtual UClass* GetSupportedClass() const override { return USharedObjectPool::StaticClass(); }
	virtual FColor GetTypeColor() const override { return FColor(255,255,255); }
	//
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
