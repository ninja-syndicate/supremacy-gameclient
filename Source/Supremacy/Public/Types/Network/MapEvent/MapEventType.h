#pragma once

#include "CoreMinimal.h"
#include "MapEventType.generated.h"

UENUM(BlueprintType)
enum class EMapEventType : uint8
{
	MapEventType_AirstrikeExplosions UMETA(DisplayName = "Airstrike Explosions", ToolTip = "The locations of airstrike missile impacts."),
	MapEventType_LandmineActivations UMETA(DisplayName = "Landmine Activations", ToolTop = "The id, location and faction of a mine that got activated."),
	MapEventType_LandmineExplosions UMETA(DisplayName = "Landmine Explosions", ToolTip = "The ids of mines that exploded."),
	MapEventType_PickupLanded UMETA(DisplayName = "Pickup Landed", ToolTip = "The id and location of a pickup that landed."),
	MapEventType_PickupUsed UMETA(DisplayName = "Pickup Removed", ToolTip = "The id of a pickup that got used."),
	MapEventType_HiveHexUpdate UMETA(DisplayName = "Hive Hex Update", ToolTip = "Update to the raised status of hexes in The Hive map."),
};
