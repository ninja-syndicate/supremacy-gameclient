#pragma once

#include "CoreMinimal.h"
#include "MapEventType.generated.h"

UENUM(BlueprintType)
enum class EMapEventType : uint8
{
	MapEventType_AirstrikeExplosions UMETA(DisplayName = "Airstrike Explosions", ToolTip = "The locations of airstrike missile impacts."),
	MapEventType_LandmineActivations UMETA(DisplayName = "Landmine Activations", ToolTop = "The id, location and faction of a mine that got activated."),
	MapEventType_LandmineExplosions UMETA(DisplayName = "Landmine Explosions", ToolTip = "The ids of mines that exploded."),
	MapEventType_HiveState UMETA(DisplayName = "Hive State", ToolTip = "The full state of The Hive map."),
	MapEventType_HiveHexRaised UMETA(DisplayName = "Hive Hex Raised", ToolTip = "The ids of the hexes that have recently raised."),
	MapEventType_HiveHexLowered UMETA(DisplayName = "Hive Hex Lowered", ToolTip = "The ids of the hexes that have recently lowered."),
};
