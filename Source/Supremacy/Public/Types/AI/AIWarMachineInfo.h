#pragma once

#include "CoreMinimal.h"
#include "AIWeaponInfo.h"
#include "AIWarMachineInfo.generated.h"

/**
* War machine info sent to the AI on start.
*
* These details have to match up with interface that AI script war machine info type expects.
* Note that the names have to match up with the script interface properties naming convention.
*/
USTRUCT(BlueprintType)
struct FAIWarMachineInfo {
	GENERATED_BODY()

public:
	/** The unique hash of the war machine. Used for identification. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString Hash;

	/** The location of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Location = FVector3f::ZeroVector;

	/** The rotation (roll, pitch, yaw) of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Rotation = FVector3f::ZeroVector;

	/** The velocity of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Velocity = FVector3f::ZeroVector;

	// TODO: Make an enum of faction for much faster access?
	/** The faction ID of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString FactionID;

	/** The name of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString Name;

	/** The model name of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString Model;

	/** The health of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float Health = 0;

	/** The max health of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float HealthMax = 0;

	/** The shield of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float Shield = 0;

	/** The max shield of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float ShieldMax = 0;

	/** The rate at which the shield is recharged when out of combat (shields per second). */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float ShieldRechargeRate = 0;

	/** The maximum movement speed (cm/s) of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float MaxSpeed = 0;

	/** All the weapons this war machine has. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIWeaponInfo> Weapons;

	/** All the abilities this war machine can perform. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	TArray<FString> Abilities;

	FAIWarMachineInfo() {}
};
