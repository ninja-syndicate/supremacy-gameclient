#pragma once
#include "MapDetails.h"
#include "Types/BattleZone.h"

#include "PayloadMapDetails.generated.h"

USTRUCT(BlueprintType)
struct FPayloadMapDetails {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMapDetails Details;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBattleZone> Battle_Zones;
};
