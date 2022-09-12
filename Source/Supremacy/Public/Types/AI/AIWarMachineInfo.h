#pragma once

#include "CoreMinimal.h"
#include "AIWeaponInfo.h"
#include "GameplayTagContainer.h"
#include "AIWarMachineInfo.generated.h"

/**
* War machine info sent to the AI on start.
*
* These details have to match up with interface that AI script war machine info type expects.
* Note that the names have to be in camelCase to match up with the script interface properties naming convention.
* JSON parser will need to convert PascalCase to camelCase if we want to remove this limitation.
*/
USTRUCT(BlueprintType)
struct FAIWarMachineInfo {
	GENERATED_BODY()

public:
	/** The unique hash of the weapon. Used for identification. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString hash;

	/** The location of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f location = FVector3f::ZeroVector;

	/** The rotation (roll, pitch, yaw) of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f rotation = FVector3f::ZeroVector;

	/** The velocity of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FVector3f velocity = FVector3f::ZeroVector;

	// TODO: Make an enum of faction for much faster access?
	/** The faction ID of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString factionID;

	/** The name of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString name;

	/** The model name of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	FString model;

	/** The health of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float health = 0;

	/** The max health of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float healthMax = 0;

	/** The shield of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float shield = 0;

	/** The max shield of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float shieldMax = 0;

	/** The rate at which the shield is recharged when out of combat (shields per second). */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float shieldRechargeRate = 0;

	/** The maximum movement speed (cm/s) of the war machine. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	float maxSpeed = 0;

	/** All the weapons this war machine has. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	TArray<FAIWeaponInfo> weapons;

	/** All the abilities this war machine can perform. */
	UPROPERTY(Category = "AI War Machine Info", EditAnywhere, BlueprintReadWrite)
	TArray<FString> abilities;

	FAIWarMachineInfo() {}
};
