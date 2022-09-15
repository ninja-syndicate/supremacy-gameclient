#pragma once

#include "CoreMinimal.h"
#include "AIDamageInfo.generated.h"

/**
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIDamageInfo {
	GENERATED_BODY()

public:
	/** The amount of damage received. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	float Amount = 0;

	// TODO: Probably use enum or string.
	/** The type of the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	int Type = 0;

	/** The normalized direction of the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FVector3f Direction = FVector3f::ZeroVector;

	/** Whether the damage is from allies. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	bool IsFriendly = false;

	/** Whether the damage is done to shield. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	bool IsShieldDamage = false;

	/** The hash of the weapon that caused the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString InstigatorHash;

	/** The hash of the weapon that caused the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString WeaponHash;

	/** The name of the ewapon that caused the damage. For damage with no weaponHash such as abilities. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString WeaponName;
	
	FAIDamageInfo() {}
};
