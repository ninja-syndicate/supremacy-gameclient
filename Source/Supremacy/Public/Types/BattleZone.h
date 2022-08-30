#pragma once

#include "CoreMinimal.h"
#include "BattleZone.generated.h"

USTRUCT(BlueprintType)
struct FBattleZone {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Shrink_Time;

	FBattleZone(): Location(FVector(0, 0, 0)), Radius(0), Time(0), Shrink_Time(0)
	{}
};

USTRUCT(BlueprintType)
struct FBattleZoneConfig {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBattleZone> Zones;
};

USTRUCT(BlueprintType)
struct FBattleZoneConfigList {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBattleZoneConfig> Configs;
};

USTRUCT(BlueprintType)
struct FBattleZoneConfigListMap {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FBattleZoneConfigList> Battle_Zones;
};