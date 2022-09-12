#pragma once

#include "CoreMinimal.h"
#include "AIDamageInfo.generated.h"

USTRUCT(BlueprintType)
struct FAIDamageInfo {
	GENERATED_BODY()

public:
	/** The amount of damage received. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	float amount = 0;

	// TODO: Probably use enum or string.
	/** The type of the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	int type = 0;

	/** The normalized direction of the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FVector3f direction = FVector3f::ZeroVector;

	/** Whether the damage is from allies. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	bool isFriendly = false;

	/** Whether the damage is done to shield. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	bool isShieldDamage = false;

	/** The hash of the weapon that caused the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString instigatorHash;

	/** The hash of the weapon that caused the damage. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString weaponHash;

	/** The name of the ewapon that caused the damage. For damage with no weaponHash such as abilities. */
	UPROPERTY(Category = "AI Damage Info", EditAnywhere, BlueprintReadWrite)
	FString weaponName;
	
	FAIDamageInfo() {}
};
