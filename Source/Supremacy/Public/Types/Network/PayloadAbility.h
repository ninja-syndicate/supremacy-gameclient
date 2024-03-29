#pragma once

#include "Types/AbilityID.h"
#include "PayloadAbility.generated.h"

USTRUCT(BlueprintType)
struct FPayloadAbility {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityID Game_Client_Ability_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Event_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Triggered_By_User_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Triggered_By_Username;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Game_Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Game_Location_End;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString War_Machine_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Faction_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Target_War_Machine_Hash;

	FPayloadAbility(): Game_Client_Ability_ID(EAbilityID::AbilityID_Airstrike), Game_Location(FVector2D(0, 0)), Game_Location_End(FVector2D(0, 0))
	{}
};
