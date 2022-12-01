#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

//~ Note that gameplay tags declared here will be auto-included on editor start.

/** Used for the mech actor. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Mech);
/** Used for shield damageable "Actor". */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Shield);
/** A gameplay tag for the Weapon "Actor". */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon);
/** Used for damageable "Actor". */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damageable);
/** A gameplay tag for the Power Core "Actor". */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PowerCore);
/** Whether the weapon supports arced shooting. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon_Arced);
/** The weapon is capable of doing melee attack. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon_Melee);
/** The weapon can be fired. E.g. Projectile weapon. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon_Fireable);
/** Primary weapon. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon_Primary);
/** Secondary weapon. E.g. Rocket Pods */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Weapon_Secondary);