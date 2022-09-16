#pragma once

#include "CoreMinimal.h"
#include "AIWeaponInfo.generated.h"

/**
 * Weapon Info sent to the AI on start.
 *
 * These details have to match up with interface that AI script Weapon Info type expects.
 * Note that the names have to match up with the script interface properties naming convention.
 */
USTRUCT(BlueprintType)
struct FAIWeaponInfo {
	GENERATED_BODY()

public:
	/** The unique hash of the weapon. Used for identification. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString Hash;

	/** The weapon name. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString Name;

	/** The weapon model. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString Model;

	/** The weapon skin. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	FString Skin;

	/** The weapon damage dealt per shot/projectile. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float Damage = 0;

	/** The weapon damage falloff distance. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float DamageFalloff = 0;

	/** How much the damage decreases by per km. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float DamageFalloffRate = 0;

	/** Radial damage radius. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float RadialDamageRadius = 0;

	/** The weapon radial damage falloff. Must be between 0 and RadialDamageRadius to have any effects. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float RadialDamageFalloff = 0;

	// TODO: Probably use enum/string.
	/** Damage type. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int DamageType = 0;

	/** The spread of the weapon. Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float Spread = 0;

	/** The number of rounds that can be fired per minute. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float RateOfFire = 0;

	/** The number of rounds per min within the burst of fire (rate of fire is used for the time between bursts.) */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float BurstRateOfFire = 0;

	/** The speed of the weapon's projectiles in cm/s. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed = 0;

	/** The number of projectiles fired per shot/burst. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int ProjectileAmount = 0;

	/** The number of seconds it takes to start firing (e.g. miniguns). */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	float ChargeTime = 0;

	/** The current weapon ammo. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int CurrentAmmo = 0;

	/** The maximum ammo capacity of this weapon. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	int MaxAmmo = 0;

	/** The weapon tags. These are used for identification of its type. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags;

	/** The slot at which this weapon is attached to. */
	UPROPERTY(Category = "AI Weapon Info", EditAnywhere, BlueprintReadWrite)
 	int Slot = 0;
	
	FAIWeaponInfo() {}
};
