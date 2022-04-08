#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BlackboardDataRow.generated.h"

/** 
  * Structure that defines a blackboard data row.
  */
USTRUCT(BlueprintType)
struct FBlackboardDataRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blackboard Data Row")
    FName BlackboardKeyEntryName;
};