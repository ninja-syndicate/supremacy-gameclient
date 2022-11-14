#pragma once

#include "CoreMinimal.h"
#include "SupremacyMatchState.generated.h"

UENUM(BlueprintType)
enum class ESupremacyMatchState : uint8
{
	GameState_Default,
	GameState_MapIntro,
	GameState_MechIntro,
	GameState_Battle,
	GameState_RoundEnd,
	GameState_GameEnd,
	GameState_Loading
};