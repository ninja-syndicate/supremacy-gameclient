#pragma once

#include "CoreMinimal.h"
#include "Types/WarMachineStruct.h"
#include "K9PatrolPackAbilityStruct.generated.h"

USTRUCT(BlueprintType)
struct FK9PatrolPackAbilityStruct {
	GENERATED_BODY()
public:
	/** The maximum patrol radius from the given spawn point. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolRadius = 0;

	/** The amount of patrol dogs to spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnAmount = 0;

	/** The patrol dog stats. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWarMachineStruct Stats;

	FK9PatrolPackAbilityStruct() {}
};