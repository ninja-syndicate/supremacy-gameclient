#pragma once

#include "CoreMinimal.h"
#include "DamageHistory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Network/BattleCommand.h"
#include "Types/WarMachineStruct.h"
#include "BPFL_StructConverters.generated.h"

UCLASS()
class SUPREMACY_API UBPFL_StructConverters final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="To WarMachineStruct (From WarMachineServerStruct)", CompactNodeTitle = "->", BlueprintAutocast))
	static FWarMachineStruct Conv_WarMachineServerStructToWarMachineStruct(const FWarMachineServerStruct& WarMachine)
	{
		return FWarMachineStruct(WarMachine);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To Faction (From FactionServer)", CompactNodeTitle = "->", BlueprintAutocast))
	static FFaction Conv_FactionServerToFaction(const FFactionServer& FactionServer)
	{
		return FFaction(FactionServer);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To ERarity (From String)", CompactNodeTitle = "->", BlueprintAutocast))
	static ERarity Conv_StringToERarity(const FString& RarityString)
	{
		return StringToERarity[RarityString];
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To DamageHistoryResultItem (From DamageHistoryItem)", CompactNodeTitle = "->", BlueprintAutocast))
	static FDamageHistoryResultItem Conv_DamageHistoryItemToDamageHistoryResultItem(const FDamageHistoryItem& DamageHistoryItem)
	{
		return FDamageHistoryResultItem(DamageHistoryItem);
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="To String (From BattleCommand)", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_BattleCommandToString(const EBattleCommand& BattleCommand)
	{
		return BattleCommandToString[BattleCommand];
	}
	
};
