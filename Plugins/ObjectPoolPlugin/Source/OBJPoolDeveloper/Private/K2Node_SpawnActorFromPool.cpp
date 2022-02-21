//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///			Copyright 2019 (C) Bruno Xavier B. Leite
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "K2Node_SpawnActorFromPool.h"

#include "GameFramework/Actor.h"
#include "UObject/UnrealType.h"
#include "Engine/EngineTypes.h"

#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet/GameplayStatics.h"
#include "KismetCompilerMisc.h"
#include "KismetCompiler.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "EdGraphSchema_K2.h"
#include "EdGraph/EdGraph.h"

#include "K2Node_CallFunction.h"
#include "K2Node_EnumLiteral.h"
#include "K2Node_Select.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FK2Node_SpawnActorFromPoolHelper {
	static FName PoolPinName;
	static FName ActorPinName;
	static FName OwnerPinName;
	static FName SuccessPinName;
	static FName TemplatePinName;
	static FName ReconstructPinName;
	static FName WorldContextPinName;
	static FName SpawnOptionsPinName;
	static FName SpawnTransformPinName;
	static FName NoCollisionFailPinName;
	static FName CollisionHandlingOverridePinName;
};

FName FK2Node_SpawnActorFromPoolHelper::ActorPinName(TEXT("Actor"));
FName FK2Node_SpawnActorFromPoolHelper::OwnerPinName(TEXT("Owner"));
FName FK2Node_SpawnActorFromPoolHelper::PoolPinName(TEXT("ObjectPool"));
FName FK2Node_SpawnActorFromPoolHelper::TemplatePinName(TEXT("PooledClass"));
FName FK2Node_SpawnActorFromPoolHelper::ReconstructPinName(TEXT("Reconstruct"));
FName FK2Node_SpawnActorFromPoolHelper::SuccessPinName(TEXT("SpawnSuccessful"));
FName FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName(TEXT("SpawnOptions"));
FName FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName(TEXT("SpawnTransform"));
FName FK2Node_SpawnActorFromPoolHelper::WorldContextPinName(TEXT("WorldContextObject"));
FName FK2Node_SpawnActorFromPoolHelper::NoCollisionFailPinName(TEXT("SpawnEvenIfColliding"));	
FName FK2Node_SpawnActorFromPoolHelper::CollisionHandlingOverridePinName(TEXT("CollisionHandlingOverride"));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOCTEXT_NAMESPACE "Synaptech"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UK2Node_SpawnActorFromPool::UK2Node_SpawnActorFromPool(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
	NodeTooltip = LOCTEXT("NodeTooltip", "Attempts to Spawn from Pool an Inactive Actor. Creates then Spawns a fully new Actor if there's none available in the Pool and 'Instantiate On Demand' is checked on Project Settings.");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FText UK2Node_SpawnActorFromPool::GetNodeTitle(ENodeTitleType::Type TitleType) const {
	FText NodeTitle = NSLOCTEXT("K2Node","SpawnActorFromPool_BaseTitle","Spawn Actor From Pool ...");
	//
	UEdGraphPin* PoolPin = GetPoolPin();
	if (!PoolPin||(PoolPin->LinkedTo.Num()==0)) {return NodeTitle;}
	//
	if (TitleType != ENodeTitleType::MenuTitle) {
		if (UEdGraphPin* ClassPin = GetTemplatePin()) {
			if (ClassPin->LinkedTo.Num()>0) {
				NodeTitle = NSLOCTEXT("K2Node","SpawnActorFromPool_Unknown","Spawn Actor From Pool");
			} else if (ClassPin->DefaultObject == nullptr) {
				NodeTitle = NSLOCTEXT("K2Node", "SpawnActorFromPool_NONE", "Spawn Actor From Pool (NONE)");
			} else {
				if (CachedNodeTitle.IsOutOfDate(this)) {
					FText ClassName;
					if (UClass* PickedClass = Cast<UClass>(ClassPin->DefaultObject)) {ClassName=PickedClass->GetDisplayNameText();}
					//
					FFormatNamedArguments Args;
					Args.Add(TEXT("Name"),ClassName);
					CachedNodeTitle.SetCachedText(FText::Format(NSLOCTEXT("K2Node","SpawnActorFromPool_Class","Spawn Actor From Pool :: {Name}"),Args),this);
				} NodeTitle = CachedNodeTitle;
			}///
		} else {NodeTitle=NSLOCTEXT("K2Node","SpawnActor_Title_NONE","SpawnActor NONE");}
	} return NodeTitle;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UK2Node_SpawnActorFromPool::AllocateDefaultPins() {
	Super::AllocateDefaultPins(); Pins.Empty();
	//
	//
	UScriptStruct* TransformStruct = TBaseStructure<FTransform>::Get();
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEnum* const CHO_Enum = FindObjectChecked<UEnum>(ANY_PACKAGE,TEXT("ESpawnActorCollisionHandlingMethod"),true);
	//
	/// Execution Pins.
	FEdGraphPinType PNT_Exec(K2Schema->PC_Exec,TEXT(""),nullptr,EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Bool(K2Schema->PC_Boolean,TEXT(""),nullptr,EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_CHO_Enum(K2Schema->PC_Byte,TEXT(""),CHO_Enum,EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Transform(K2Schema->PC_Struct,TEXT(""),TransformStruct,EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Owner(K2Schema->PC_Object,TEXT(""),AActor::StaticClass(),EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Object(K2Schema->PC_Object,TEXT(""),UObject::StaticClass(),EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Class(K2Schema->PC_Class,TEXT(""),APooledActor::StaticClass(),EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_Result(K2Schema->PC_Object,TEXT(""),APooledActor::StaticClass(),EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_OBJPool(K2Schema->PC_Object,TEXT(""),UObjectPool::StaticClass(),EPinContainerType::None,false,FEdGraphTerminalType());
	FEdGraphPinType PNT_SpawnOptions(K2Schema->PC_Struct,TEXT(""),FPoolSpawnOptions::StaticStruct(),EPinContainerType::None,false,FEdGraphTerminalType());
	//
	UEdGraphPin* PIN_Spawn = CreatePin(EGPD_Input,PNT_Exec,K2Schema->PN_Execute);
	UEdGraphPin* PIN_Finish = CreatePin(EGPD_Output,PNT_Exec,K2Schema->PN_Then);
	//
	PIN_Spawn->PinFriendlyName = LOCTEXT("Spawn","Spawn");
	PIN_Finish->PinFriendlyName = LOCTEXT("Finished","Finished Spawning");
	//
	//
	/// World Context Pin.
	if (GetBlueprint()->ParentClass->HasMetaDataHierarchical(FBlueprintMetadata::MD_ShowWorldContextPin)) {
		CreatePin(EGPD_Input,PNT_Object,FK2Node_SpawnActorFromPoolHelper::WorldContextPinName);
	}///
	//
	/// Pooled Class Pin.
	UEdGraphPin* PIN_Class = CreatePin(EGPD_Input,PNT_Class,FK2Node_SpawnActorFromPoolHelper::TemplatePinName);
	//
	/// Pool Pin.
	UEdGraphPin* PIN_Pool = CreatePin(EGPD_Input,PNT_OBJPool,FK2Node_SpawnActorFromPoolHelper::PoolPinName);
	//
	/// Collision Handling Pin.
	UEdGraphPin* const PIN_CollisionHandlingOverride = CreatePin(EGPD_Input,PNT_CHO_Enum,FK2Node_SpawnActorFromPoolHelper::CollisionHandlingOverridePinName);
	PIN_CollisionHandlingOverride->DefaultValue = CHO_Enum->GetNameStringByIndex(static_cast<int>(ESpawnActorCollisionHandlingMethod::Undefined));
	//
	/// Default Pins.
	UEdGraphPin* PIN_Transform = CreatePin(EGPD_Input,PNT_Transform,FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName);
	UEdGraphPin* PIN_Options = CreatePin(EGPD_Input,PNT_SpawnOptions,FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName);
	UEdGraphPin* PIN_Reconstruct = CreatePin(EGPD_Input,PNT_Bool,FK2Node_SpawnActorFromPoolHelper::ReconstructPinName);
	UEdGraphPin* PIN_Success = CreatePin(EGPD_Output,PNT_Bool,FK2Node_SpawnActorFromPoolHelper::SuccessPinName);
	UEdGraphPin* PIN_Result = CreatePin(EGPD_Output,PNT_Result,K2Schema->PN_ReturnValue);
	//
	/// Owner Pin.
	UEdGraphPin* PIN_Owner = CreatePin(EGPD_Input,PNT_Owner,FK2Node_SpawnActorFromPoolHelper::OwnerPinName);
	PIN_Owner->bAdvancedView = true;
	//
	//
	if (ENodeAdvancedPins::NoPins==AdvancedPinDisplay) {
		AdvancedPinDisplay = ENodeAdvancedPins::Hidden;
	}///
	//
	FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UClass* UK2Node_SpawnActorFromPool::GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch) const {
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;
	//
	UClass* ClassToSpawn = nullptr;
	UEdGraphPin* ClassPin = GetTemplatePin(PinsToSearch);
	//
	if (ClassPin && ClassPin->DefaultObject && ClassPin->LinkedTo.Num()==0) {
		ClassToSpawn = CastChecked<UClass>(ClassPin->DefaultObject);
	} else if (ClassPin && ClassPin->LinkedTo.Num()) {
		UEdGraphPin* ClassSource = ClassPin->LinkedTo[0];
		ClassToSpawn = ClassSource ? Cast<UClass>(ClassSource->PinType.PinSubCategoryObject.Get()) : nullptr;
	}///
	//
	return ClassToSpawn;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UK2Node_SpawnActorFromPool::CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins) {
	if (InClass==nullptr) {return;}
	//
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	const UObject* const ClassDefaultObject = InClass->GetDefaultObject(false);
	//
	for (TFieldIterator<FProperty> PIT(InClass, EFieldIteratorFlags::IncludeSuper); PIT; ++PIT) {
		FProperty* Property = *PIT;
		UClass* PropertyClass = CastChecked<UClass>(Property->GetOwner<UObject>());
		//
		const bool bIsDelegate = Property->IsA(FMulticastDelegateProperty::StaticClass());
		const bool bIsExposedToSpawn = UEdGraphSchema_K2::IsPropertyExposedOnSpawn(Property);
		const bool bIsSettableExternally = !Property->HasAnyPropertyFlags(CPF_DisableEditOnInstance);
		//
		if (bIsExposedToSpawn && !Property->HasAnyPropertyFlags(CPF_Parm) && bIsSettableExternally && Property->HasAllPropertyFlags(CPF_BlueprintVisible)
		&& !bIsDelegate && (nullptr==FindPin(Property->GetFName())) && FBlueprintEditorUtils::PropertyStillExists(Property)) {
			if (UEdGraphPin* Pin = CreatePin(EGPD_Input,NAME_None,Property->GetFName())) {
				K2Schema->ConvertPropertyToPinType(Property,Pin->PinType);
				if (OutClassPins) {OutClassPins->Add(Pin);}
				//
				if (ClassDefaultObject && K2Schema->PinDefaultValueIsEditable(*Pin)) {
					FString DefaultValueAsString;
					const bool bDefaultValueSet = FBlueprintEditorUtils::PropertyValueToString(Property,reinterpret_cast<const uint8*>(ClassDefaultObject),DefaultValueAsString);
					//
					K2Schema->SetPinAutogeneratedDefaultValue(Pin,DefaultValueAsString);
				} K2Schema->ConstructBasicPinTooltip(*Pin,Property->GetToolTipText(),Pin->PinToolTip);
		}}//////
	}///
	//
	UEdGraphPin* ResultPin = GetResultPin();
	ResultPin->PinType.PinSubCategoryObject = InClass->GetAuthoritativeClass();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UK2Node_SpawnActorFromPool::ExpandNode(class FKismetCompilerContext &CompilerContext, UEdGraph* SourceGraph) {
	Super::ExpandNode(CompilerContext,SourceGraph);
	if (this->IsPendingKill()||!SourceGraph->IsValidLowLevelFast()||SourceGraph->IsPendingKill()) {return;}
	//
	static FName BeginSpawningBlueprintFuncName = GET_FUNCTION_NAME_CHECKED(UObjectPool,BeginDeferredSpawnFromPool);
	static FName FinishSpawningFuncName = GET_FUNCTION_NAME_CHECKED(UObjectPool,FinishDeferredSpawnFromPool);
	//
	UK2Node_SpawnActorFromPool* SpawnNode = this;
	UEdGraphPin* SpawnPoolPin = SpawnNode->GetPoolPin();
	UEdGraphPin* SpawnNodeExec = SpawnNode->GetExecPin();
	UEdGraphPin* SpawnNodeThen = SpawnNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = SpawnNode->GetResultPin();
	UEdGraphPin* SpawnSuccessPin = SpawnNode->GetSuccessPin();
	UEdGraphPin* SpawnNodeOwnerPin = SpawnNode->GetOwnerPin();
	UEdGraphPin* SpawnTemplatePin = SpawnNode->GetTemplatePin();
	UEdGraphPin* SpawnNodeOptions = SpawnNode->GetSpawnOptionsPin();
	UEdGraphPin* SpawnWorldContextPin = SpawnNode->GetWorldContextPin();
	UEdGraphPin* SpawnNodeTransform = SpawnNode->GetSpawnTransformPin();
	UEdGraphPin* SpawnNodeReconstructPin = SpawnNode->GetReconstructPin();
	UEdGraphPin* SpawnNodeCollisionHandlingOverride = GetCollisionHandlingOverridePin();
	//
	//
	if (!SpawnPoolPin||(SpawnPoolPin->LinkedTo.Num()==0)) {
		CompilerContext.MessageLog.Error(*LOCTEXT("SpawnActorFromPool_Pool_Error","Spawn Node: @@ must have a @@ specified!").ToString(),SpawnNode,SpawnPoolPin);
		SpawnNode->BreakAllNodeLinks();
	return;}
	//
	//
	UClass* ClassToSpawn = GetClassToSpawn();
	if (ClassToSpawn==nullptr) {
		CompilerContext.MessageLog.Error(*LOCTEXT("SpawnActorFromPool_Pool_Error","Spawn Node: @@ must be a valid Template @@ within target Pool Component (check Component Default 'Template Classes' Map).").ToString(),SpawnNode,SpawnTemplatePin);
		SpawnNode->BreakAllNodeLinks();
	return;}
	//
	//
	UK2Node_CallFunction* CallBeginSpawnNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(SpawnNode,SourceGraph);
	CallBeginSpawnNode->FunctionReference.SetExternalMember(BeginSpawningBlueprintFuncName,UObjectPool::StaticClass());
	CallBeginSpawnNode->AllocateDefaultPins();
	//
	UEdGraphPin* CallBeginExec = CallBeginSpawnNode->GetExecPin();
	UEdGraphPin* CallBeginResult = CallBeginSpawnNode->GetReturnValuePin();
	UEdGraphPin* CallBeginOwnerPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::OwnerPinName);
	UEdGraphPin* CallBeginActorPoolPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::PoolPinName);
	UEdGraphPin* CallBeginSuccessPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SuccessPinName);
	UEdGraphPin* CallBeginTemplatePin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::TemplatePinName);
	UEdGraphPin* CallBeginOptions = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName);
	UEdGraphPin* CallBeginTransform = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName);
	UEdGraphPin* CallBeginReconstructPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::ReconstructPinName);
	UEdGraphPin* CallBeginWorldContextPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::WorldContextPinName);
	UEdGraphPin* CallBeginCollisionHandlingOverride = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::CollisionHandlingOverridePinName);
	//
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec,*CallBeginExec);
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeOptions,*CallBeginOptions);
	CompilerContext.MovePinLinksToIntermediate(*SpawnPoolPin,*CallBeginActorPoolPin);
	CompilerContext.MovePinLinksToIntermediate(*SpawnSuccessPin,*CallBeginSuccessPin);
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeTransform,*CallBeginTransform);
	CompilerContext.MovePinLinksToIntermediate(*SpawnTemplatePin,*CallBeginTemplatePin);
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeReconstructPin,*CallBeginReconstructPin);
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeCollisionHandlingOverride,*CallBeginCollisionHandlingOverride);
	//
	if (SpawnWorldContextPin) {CompilerContext.MovePinLinksToIntermediate(*SpawnWorldContextPin,*CallBeginWorldContextPin);}
	if (SpawnNodeOwnerPin!=nullptr) {CompilerContext.MovePinLinksToIntermediate(*SpawnNodeOwnerPin,*CallBeginOwnerPin);}
	//
	//
	UK2Node_CallFunction* CallFinishSpawnNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(SpawnNode,SourceGraph);
	CallFinishSpawnNode->FunctionReference.SetExternalMember(FinishSpawningFuncName,UObjectPool::StaticClass());
	CallFinishSpawnNode->AllocateDefaultPins();
	//
	UEdGraphPin* CallFinishExec = CallFinishSpawnNode->GetExecPin();
	UEdGraphPin* CallFinishThen = CallFinishSpawnNode->GetThenPin();
	UEdGraphPin* CallFinishResult = CallFinishSpawnNode->GetReturnValuePin();
	UEdGraphPin* CallFinishActor = CallFinishSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::ActorPinName);
	UEdGraphPin* CallFinishReconstruct = CallFinishSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::ReconstructPinName);
	UEdGraphPin* CallFinishTransform = CallFinishSpawnNode->FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName);
	//
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen,*CallFinishThen);
	CompilerContext.CopyPinLinksToIntermediate(*CallBeginTransform,*CallFinishTransform);
	CompilerContext.MovePinLinksToIntermediate(*CallBeginReconstructPin,*CallFinishReconstruct);
	//
	CallBeginResult->MakeLinkTo(CallFinishActor);
	CallFinishResult->PinType = SpawnNodeResult->PinType;
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult,*CallFinishResult);
	//
	//
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext,SourceGraph,CallBeginSpawnNode,SpawnNode,CallBeginResult,ClassToSpawn);
	LastThen->MakeLinkTo(CallFinishExec);
	//
	SpawnNode->BreakAllNodeLinks();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UK2Node_SpawnActorFromPool::MaybeUpdateCollisionPin(TArray<UEdGraphPin*> &OldPins) {
	for (UEdGraphPin* Pin : OldPins) {
		if (Pin->PinName == FK2Node_SpawnActorFromPoolHelper::NoCollisionFailPinName) {
			bool bHadOldCollisionPin = true;
			if (Pin->LinkedTo.Num() == 0) {
				bool const bOldCollisionPinValue = (Pin->DefaultValue == FString(TEXT("true")));
				UEdGraphPin* const CollisionHandlingOverridePin = GetCollisionHandlingOverridePin();
				if (CollisionHandlingOverridePin) {
					UEnum const* const MethodEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("ESpawnActorCollisionHandlingMethod"), true);
					CollisionHandlingOverridePin->DefaultValue =
					bOldCollisionPinValue
					? MethodEnum->GetNameStringByIndex(static_cast<int>(ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
					: MethodEnum->GetNameStringByIndex(static_cast<int>(ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding));
				}///
			} else {
				UEdGraphPin* const CollisionHandlingOverridePin = GetCollisionHandlingOverridePin();
				if (CollisionHandlingOverridePin==nullptr) {return;}
				//
				UEnum* const MethodEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("ESpawnActorCollisionHandlingMethod"), true);
				//
				FGraphNodeCreator<UK2Node_EnumLiteral> AlwaysSpawnLiteralCreator(*GetGraph());
				UK2Node_EnumLiteral* const AlwaysSpawnLiteralNode = AlwaysSpawnLiteralCreator.CreateNode();
				AlwaysSpawnLiteralNode->Enum = MethodEnum;
				AlwaysSpawnLiteralNode->NodePosX = NodePosX;
				AlwaysSpawnLiteralNode->NodePosY = NodePosY;
				AlwaysSpawnLiteralCreator.Finalize();
				//
				FGraphNodeCreator<UK2Node_EnumLiteral> AdjustIfNecessaryLiteralCreator(*GetGraph());
				UK2Node_EnumLiteral* const AdjustIfNecessaryLiteralNode = AdjustIfNecessaryLiteralCreator.CreateNode();
				AdjustIfNecessaryLiteralNode->Enum = MethodEnum;
				AdjustIfNecessaryLiteralNode->NodePosX = NodePosX;
				AdjustIfNecessaryLiteralNode->NodePosY = NodePosY;
				AdjustIfNecessaryLiteralCreator.Finalize();
				//
				FGraphNodeCreator<UK2Node_Select> SelectCreator(*GetGraph());
				UK2Node_Select* const SelectNode = SelectCreator.CreateNode();
				SelectNode->NodePosX = NodePosX;
				SelectNode->NodePosY = NodePosY;
				SelectCreator.Finalize();
				//
				auto FindEnumInputPin = [](UK2Node_EnumLiteral const* Node) {
					for (UEdGraphPin* NodePin : Node->Pins) {
						if (NodePin->PinName == Node->GetEnumInputPinName()) {return NodePin;}
					} return (UEdGraphPin*)nullptr;
				};//
				//
				UEdGraphPin* const AlwaysSpawnLiteralNodeInputPin = FindEnumInputPin(AlwaysSpawnLiteralNode);
				UEdGraphPin* const AdjustIfNecessaryLiteralInputPin = FindEnumInputPin(AdjustIfNecessaryLiteralNode);
				//
				TArray<UEdGraphPin*> SelectOptionPins;
				SelectNode->GetOptionPins(SelectOptionPins);
				UEdGraphPin* const SelectIndexPin = SelectNode->GetIndexPin();
				//
				auto FindResultPin = [](UK2Node const* Node) {
					for (UEdGraphPin* NodePin : Node->Pins) {
						if (EEdGraphPinDirection::EGPD_Output == NodePin->Direction) {return NodePin;}
					} return (UEdGraphPin*)nullptr;
				};//
				//
				UEdGraphPin* const AlwaysSpawnLiteralNodeResultPin = FindResultPin(AlwaysSpawnLiteralNode);
				UEdGraphPin* const AdjustIfNecessaryLiteralResultPin = FindResultPin(AdjustIfNecessaryLiteralNode);
				//
				if (AlwaysSpawnLiteralNodeResultPin==nullptr) {return;}
				if (AdjustIfNecessaryLiteralResultPin==nullptr) {return;}
				//
				UEdGraphPin* const OldBoolPin = Pin->LinkedTo[0];
				if (OldBoolPin==nullptr) {return;}
				//
				AlwaysSpawnLiteralNodeInputPin->DefaultValue = MethodEnum->GetNameStringByIndex(static_cast<int>(ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
				AdjustIfNecessaryLiteralInputPin->DefaultValue = MethodEnum->GetNameStringByIndex(static_cast<int>(ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding));
				//
				OldBoolPin->BreakLinkTo(Pin);
				OldBoolPin->MakeLinkTo(SelectIndexPin);
				//
				AlwaysSpawnLiteralNodeResultPin->MakeLinkTo(SelectOptionPins[0]);
				AdjustIfNecessaryLiteralResultPin->MakeLinkTo(SelectOptionPins[1]);
				//
				UEdGraphPin* const SelectOutputPin = SelectNode->GetReturnValuePin();
				if (SelectOutputPin==nullptr) {return;}
				//
				SelectOutputPin->MakeLinkTo(CollisionHandlingOverridePin);
				//
				SelectNode->NotifyPinConnectionListChanged(SelectIndexPin);
				SelectNode->NotifyPinConnectionListChanged(SelectOutputPin);
				SelectNode->NotifyPinConnectionListChanged(SelectOptionPins[0]);
				SelectNode->NotifyPinConnectionListChanged(SelectOptionPins[1]);
			}///
		}///
	}///
}

void UK2Node_SpawnActorFromPool::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*> &OldPins) {
	AllocateDefaultPins();
	//
	UClass* ClassToSpawn = GetClassToSpawn(&OldPins);
	//
	if (ClassToSpawn) {
		TArray<UEdGraphPin*>ClassPins;
		CreatePinsForClass(ClassToSpawn,&ClassPins);
	}///
	//
	MaybeUpdateCollisionPin(OldPins);
	RestoreSplitPins(OldPins);
}

bool UK2Node_SpawnActorFromPool::IsNodeBasePin(UEdGraphPin* Pin) {
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	//
	UEdGraphPin* ParentPin = Pin->ParentPin;
	while (ParentPin) {
		if (ParentPin->PinName == FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName) {return false;}
		if (ParentPin->PinName == FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName) {return false;}
	ParentPin=ParentPin->ParentPin;}
	//
	return (
		Pin->PinName != K2Schema->PN_Then &&
		Pin->PinName != K2Schema->PN_Execute &&
		Pin->PinName != K2Schema->PN_ReturnValue &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::PoolPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::OwnerPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::SuccessPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::TemplatePinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::ReconstructPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::WorldContextPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName &&
		Pin->PinName != FK2Node_SpawnActorFromPoolHelper::CollisionHandlingOverridePinName
	);//
}

void UK2Node_SpawnActorFromPool::PostPlacedNewNode() {
	Super::PostPlacedNewNode();
	//
	UClass* ClassToSpawn = GetClassToSpawn();
	//
	if (ClassToSpawn != nullptr) {
		TArray<UEdGraphPin*> ClassPins;
		CreatePinsForClass(ClassToSpawn,&ClassPins);
	}///
}

void UK2Node_SpawnActorFromPool::OnClassPinChanged() {
 	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	//
	TArray<UEdGraphPin*> OldPins = Pins;
	TArray<UEdGraphPin*> OldClassPins;
	//
	for (int32 I=0; I<OldPins.Num(); I++) {
		UEdGraphPin* OldPin = OldPins[I];
		if (IsNodeBasePin(OldPin)) {
			Pins.Remove(OldPin);
			OldClassPins.Add(OldPin);
		}///
	}///
	//
	CachedNodeTitle.MarkDirty();
	//
	TArray<UEdGraphPin*> NewClassPins;
	UClass* ClassToSpawn = GetClassToSpawn();
	//
	if (ClassToSpawn) {CreatePinsForClass(ClassToSpawn,&NewClassPins);}
	//
	UEdGraphPin* ResultPin = GetResultPin();
	TArray<UEdGraphPin*> ResultPinConnectionList = ResultPin->LinkedTo;
	ResultPin->BreakAllPinLinks();
	//
	for (UEdGraphPin* Connections : ResultPinConnectionList) {
		K2Schema->TryCreateConnection(ResultPin,Connections);
	}///
	//
	TMap<UEdGraphPin*,UEdGraphPin*>NewPinsToOldPins;
	RewireOldPinsToNewPins(OldClassPins,NewClassPins,&NewPinsToOldPins);
	//
	DestroyPinList(OldClassPins);
	//
	UEdGraph* Graph = GetGraph();
	Graph->NotifyGraphChanged();
	//
	FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());
}

void UK2Node_SpawnActorFromPool::PinConnectionListChanged(UEdGraphPin* ChangedPin) {
	if (ChangedPin && (ChangedPin->PinName==FK2Node_SpawnActorFromPoolHelper::PoolPinName)) {OnClassPinChanged();}
	if (ChangedPin && (ChangedPin->PinName==FK2Node_SpawnActorFromPoolHelper::TemplatePinName)) {OnClassPinChanged();}
}

void UK2Node_SpawnActorFromPool::PinDefaultValueChanged(UEdGraphPin* ChangedPin) {
	if (ChangedPin && (ChangedPin->PinName==FK2Node_SpawnActorFromPoolHelper::PoolPinName)) {OnClassPinChanged();}
	if (ChangedPin && (ChangedPin->PinName==FK2Node_SpawnActorFromPoolHelper::TemplatePinName)) {OnClassPinChanged();}
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetThenPin() const {
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	//
	UEdGraphPin* Pin = FindPinChecked(K2Schema->PN_Then);
	check(Pin==nullptr||Pin->Direction==EGPD_Output); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetPoolPin(const TArray<UEdGraphPin*>* InPinsToSearch) const {
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;
	//
	UEdGraphPin* Pin = nullptr;
	for (auto PinIt = PinsToSearch->CreateConstIterator(); PinIt; ++PinIt ) {
		UEdGraphPin* TestPin = *PinIt;
		if (TestPin && TestPin->PinName==FK2Node_SpawnActorFromPoolHelper::PoolPinName) {Pin=TestPin; break;}
	}///
	//
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetTemplatePin(const TArray<UEdGraphPin*>* InPinsToSearch) const {
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;
	//
	UEdGraphPin* Pin = nullptr;
	for (auto PinIt = PinsToSearch->CreateConstIterator(); PinIt; ++PinIt ) {
		UEdGraphPin* TestPin = *PinIt;
		if (TestPin && TestPin->PinName==FK2Node_SpawnActorFromPoolHelper::TemplatePinName) {Pin=TestPin; break;}
	}///
	//
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetSpawnOptionsPin() const {
	UEdGraphPin* Pin = FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SpawnOptionsPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetSpawnTransformPin() const {
	UEdGraphPin* Pin = FindPinChecked(FK2Node_SpawnActorFromPoolHelper::SpawnTransformPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetCollisionHandlingOverridePin() const {
	UEdGraphPin* const Pin = FindPinChecked(FK2Node_SpawnActorFromPoolHelper::CollisionHandlingOverridePinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetOwnerPin() const {
	UEdGraphPin* Pin = FindPin(FK2Node_SpawnActorFromPoolHelper::OwnerPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetReconstructPin() const {
	UEdGraphPin* Pin = FindPin(FK2Node_SpawnActorFromPoolHelper::ReconstructPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetWorldContextPin() const {
	UEdGraphPin* Pin = FindPin(FK2Node_SpawnActorFromPoolHelper::WorldContextPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Input); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetSuccessPin() const {
	UEdGraphPin* Pin = FindPin(FK2Node_SpawnActorFromPoolHelper::SuccessPinName);
	check(Pin==nullptr||Pin->Direction==EGPD_Output); return Pin;
}

UEdGraphPin* UK2Node_SpawnActorFromPool::GetResultPin() const {
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEdGraphPin* Pin = FindPinChecked(K2Schema->PN_ReturnValue);
	check(Pin==nullptr||Pin->Direction==EGPD_Output); return Pin;
}

FLinearColor UK2Node_SpawnActorFromPool::GetNodeTitleColor() const {
	FColor Color = FColor(0.f,255.f,245.f);
	return FLinearColor(Color);
}

bool UK2Node_SpawnActorFromPool::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const  {
	UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(TargetGraph);
	return Super::IsCompatibleWithGraph(TargetGraph) && (!Blueprint || (FBlueprintEditorUtils::FindUserConstructionScript(Blueprint) != TargetGraph && Blueprint->GeneratedClass->GetDefaultObject()->ImplementsGetWorld()));
}

void UK2Node_SpawnActorFromPool::GetNodeAttributes( TArray<TKeyValuePair<FString, FString>> &OutNodeAttributes ) const {
	UClass* ClassToSpawn = GetClassToSpawn();
	//
	const FString ClassToSpawnStr = ClassToSpawn ? ClassToSpawn->GetName() : TEXT("InvalidClass");
	//
	OutNodeAttributes.Add(TKeyValuePair<FString,FString>(TEXT("NodeType"),TEXT("SpawnActorFromPool")));
	OutNodeAttributes.Add(TKeyValuePair<FString,FString>(TEXT("NodeClass"),GetClass()->GetName()));
	OutNodeAttributes.Add(TKeyValuePair<FString,FString>(TEXT("SpawnClass"),ClassToSpawnStr));
	OutNodeAttributes.Add(TKeyValuePair<FString,FString>(TEXT("NodeName"),GetName()));
}

FNodeHandlingFunctor* UK2Node_SpawnActorFromPool::CreateNodeHandler(FKismetCompilerContext &CompilerContext) const {
	return new FNodeHandlingFunctor(CompilerContext);
}

bool UK2Node_SpawnActorFromPool::HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const {
	UClass* SourceClass = GetClassToSpawn();
	//
	const UBlueprint* SourceBlueprint = GetBlueprint();
	const bool bResult = (SourceClass != nullptr) && (SourceClass->ClassGeneratedBy != SourceBlueprint);
	//
	if (bResult && OptionalOutput) {OptionalOutput->AddUnique(SourceClass);}
	const bool bSuperResult = Super::HasExternalDependencies(OptionalOutput);
	//
	return bSuperResult || bResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UK2Node_SpawnActorFromPool::GetPinHoverText(const UEdGraphPin &Pin, FString &HoverTextOut) const {
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	//
	if (UEdGraphPin* PoolPin = GetPoolPin()) {
		K2Schema->ConstructBasicPinTooltip(*PoolPin,LOCTEXT("PoolPinDescription","The Pool Owner of Actor Instance."),PoolPin->PinToolTip);
	}if (UEdGraphPin* ClassPin = GetTemplatePin()) {
		K2Schema->ConstructBasicPinTooltip(*ClassPin,LOCTEXT("ClassPinDescription","The Class to Spawn. Target Pool must have this Class as member of its Templates Map (Properties on Details Panel)."),ClassPin->PinToolTip);
	} if (UEdGraphPin* TransformPin = GetSpawnTransformPin()) {
		K2Schema->ConstructBasicPinTooltip(*TransformPin,LOCTEXT("TransformPinDescription","The transform to spawn the Actor with"),TransformPin->PinToolTip);
	} if (UEdGraphPin* CollisionHandlingOverridePin = GetCollisionHandlingOverridePin()) {
		K2Schema->ConstructBasicPinTooltip(*CollisionHandlingOverridePin,LOCTEXT("CollisionHandlingOverridePinDescription","Specifies how to handle collisions at the Spawn Point. If undefined,uses Actor Class Settings."),CollisionHandlingOverridePin->PinToolTip);
	} if (UEdGraphPin* OwnerPin = GetOwnerPin()) {
		K2Schema->ConstructBasicPinTooltip(*OwnerPin,LOCTEXT("OwnerPinDescription","Can be left empty; primarily used for replication or visibility."),OwnerPin->PinToolTip);
	} if (UEdGraphPin* ReconstructPin = GetReconstructPin()) {
		K2Schema->ConstructBasicPinTooltip(*ReconstructPin,LOCTEXT("ReconstructPinDescription","If checked, this will force the Spawning Actor to re-run its Construction Scripts;\nThis results on expensive respawn operation and will affect performance!\nAvoid pulling Actors every second with this option enabled."),ReconstructPin->PinToolTip);
	} if (UEdGraphPin* ResultPin = GetResultPin()) {
		K2Schema->ConstructBasicPinTooltip(*ResultPin,LOCTEXT("ResultPinDescription","The Actor Class Spawned from the Pool."),ResultPin->PinToolTip);
	} return Super::GetPinHoverText(Pin,HoverTextOut);
}

FText UK2Node_SpawnActorFromPool::GetTooltipText() const {
	return NodeTooltip;
}

FSlateIcon UK2Node_SpawnActorFromPool::GetIconAndTint(FLinearColor &OutColor) const {
	static FSlateIcon Icon(TEXT("OBJPoolStyle"),TEXT("ClassIcon.ObjectPool"));
	return Icon;
}

void UK2Node_SpawnActorFromPool::GetMenuActions(FBlueprintActionDatabaseRegistrar &ActionRegistrar) const {
	UClass* ActionKey = GetClass();
	//
	if (ActionRegistrar.IsOpenForRegistration(ActionKey)) {
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		if (NodeSpawner==nullptr) {return;}
		//
		ActionRegistrar.AddBlueprintAction(ActionKey,NodeSpawner);
	}///
}

FText UK2Node_SpawnActorFromPool::GetMenuCategory() const {
	return LOCTEXT("PoolCategory","Object Pool");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////