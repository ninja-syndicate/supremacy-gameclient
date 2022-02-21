//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "OBJPool.h"

#include "K2Node.h"
#include "CoreMinimal.h"
#include "Textures/SlateIcon.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNodeUtils.h"

#include "K2Node_SpawnActorFromPool.generated.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FBlueprintActionDatabaseRegistrar;
class UEdGraph;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class OBJPOOLDEVELOPER_API UK2Node_SpawnActorFromPool : public UK2Node {
	GENERATED_UCLASS_BODY()
private:
	void MaybeUpdateCollisionPin(TArray<UEdGraphPin*> &OldPins);
protected:
	FText NodeTooltip;
	FNodeTextCache CachedNodeTitle;
	//
	void OnClassPinChanged();
public:
	virtual void PostPlacedNewNode() override;
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual FSlateIcon GetIconAndTint(FLinearColor &OutColor) const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;
	virtual bool HasExternalDependencies(TArray<UStruct*>* OptionalOutput) const override;
	virtual void GetPinHoverText(const UEdGraphPin &Pin, FString &HoverTextOut) const override;
	virtual void ExpandNode(FKismetCompilerContext &CompilerContext, UEdGraph* SourceGraph) override;
	//
	virtual FText GetMenuCategory() const override;
	virtual bool IsNodeSafeToIgnore() const override {return true;}
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*> &OldPins) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar &ActionRegistrar) const override;
	virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>> &OutNodeAttributes ) const override;
	virtual class FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext &CompilerContext) const override;
	//
	bool IsNodeBasePin(UEdGraphPin* Pin);
	void CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins = nullptr);
	//
	UEdGraphPin* GetThenPin() const;
	UEdGraphPin* GetOwnerPin() const;
	UEdGraphPin* GetResultPin() const;
	UEdGraphPin* GetSuccessPin() const;
	UEdGraphPin* GetReconstructPin() const;
	UEdGraphPin* GetWorldContextPin() const;
	UEdGraphPin* GetSpawnOptionsPin() const;
	UEdGraphPin* GetSpawnTransformPin() const;
	UEdGraphPin* GetCollisionHandlingOverridePin() const;
	UEdGraphPin* GetPoolPin(const TArray<UEdGraphPin*>* InPinsToSearch=nullptr) const;
	UEdGraphPin* GetTemplatePin(const TArray<UEdGraphPin*>* InPinsToSearch=nullptr) const;
	//
	UClass* GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch=nullptr) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////