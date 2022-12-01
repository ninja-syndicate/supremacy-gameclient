#pragma once

#include "CoreMinimal.h"

// TODO: Provide BPFL if blueprints need to access these constants.
namespace WeaponConstants
{
	/** A tag for the main static mesh component to be used for scaling. */
	inline const FName MainStaticMeshTagName = FName("Main");
	/** A tag for the static mesh component that has barrel socket. Used for aligning the barrel to the aim location. */
	inline const FName BarrelStaticMeshTagName = FName("Barrel");
	/** The socket name for the barrel in the static mesh component. */
	inline const FName BarrelSocketName = FName("Barrel");
}