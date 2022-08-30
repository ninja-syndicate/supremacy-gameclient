#pragma once

#include "PayloadSpawnedAI.generated.h"

USTRUCT(BlueprintType)
struct FPayloadSpawnedAI {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Battle_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Participant_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString User_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Faction_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health_Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Shield_Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rotation;
	
	FPayloadSpawnedAI() : Participant_ID(0), Health_Max(0), Shield_Max(0), Location(FVector2D(0, 0)), Rotation(0)
	{}
};
