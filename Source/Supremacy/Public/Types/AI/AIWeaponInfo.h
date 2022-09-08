#pragma once

#include "CoreMinimal.h"
#include "AIWeaponInfo.generated.h"

/**
 * Weapon Info sent to the AI on start.
 *
 * These details have to match up with interface that AI script Weapon Info type expects.
 * Note that the names have to be in camelCase to match up with the script interface properties naming convention.
 * JSON parser will need to convert PascalCase to camelCase if we want to remove this limitation.
 */
USTRUCT(BlueprintType)
struct FAIWeaponInfo {
	GENERATED_BODY()

public:
	/** The unique hash of the weapon. Used for identification. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString hash;

	/** The weapon name. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString name;

	/** The weapon model. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString model;

	/** The weapon skin. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString skin;

	/** The weapon damage dealt per shot/projectile. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float damage = 0;

	/** The weapon damage falloff distance. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float damageFalloff = 0;

	/** How much the damage decreases by per km. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float damageFalloffRate = 0;

	/** Radial damage radius. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float radialDamageRadius = 0;

	/** The weapon radial damage falloff. Must be between 0 and RadialDamageRadius to have any effects. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float radialDamageFalloff = 0;

	// TODO: Probably use enum/string.
	/** Damage type. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int damageType = 0;

	/** The spread of the weapon. Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float spread = 0;

	/** The number of rounds that can be fired per minute. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float rateOfFire = 0;

	/** The number of rounds per min within the burst of fire (rate of fire is used for the time between bursts.) */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float burstRateOfFire = 0;

	/** The speed of the weapon's projectiles in cm/s. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float projectileSpeed = 0;

	/** The number of projectiles fired per shot/burst. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int projectileAmount = 0;

	/** The number of seconds it takes to start firing (e.g. miniguns). */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float chargeTime = 0;

	/** The current weapon ammo. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int currentAmmo = 0;

	/** The maximum ammo capacity of this weapon. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int maxAmmo = 0;

	/** The weapon tags. These are used for identification of its type. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	TArray<FString> tags;

	/** The slot at which this weapon is attached to. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
 	int slot = 0;
	
	FAIWeaponInfo() {}
};
