#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/WarMachineStruct.h"
#include "BPFL_StructConverters.generated.h"

UCLASS()
class SUPREMACY_API UBPFL_StructConverters final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="To FWarMachineStruct (From FWarMachineServerStruct)", CompactNodeTitle = "->", BlueprintAutocast))
	static FWarMachineStruct Conv_WarMachineServerStructToWarMachineStruct(const FWarMachineServerStruct& WarMachine)
	{
		return FWarMachineStruct(WarMachine);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To FFaction (From FFactionServer)", CompactNodeTitle = "->", BlueprintAutocast))
	static FFaction Conv_FFactionServerToFFaction(const FFactionServer& FactionServer)
	{
		return FFaction(FactionServer);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To ERarity (From String)", CompactNodeTitle = "->", BlueprintAutocast))
	static ERarity Conv_StringToERarity(const FString& RarityString)
	{
		return StringToERarity[RarityString];
	}

};
