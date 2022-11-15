#pragma once

#include "CoreMinimal.h"
#include "SupremacyMatchState.generated.h"

UENUM(BlueprintType)
enum class ESupremacyMatchState : uint8
{
	MatchState_Default,
	MatchState_MapIntro,
	MatchState_MechIntro,
	MatchState_Battle,
	MatchState_RoundEnd,
	MatchState_GameEnd,
	MatchState_Loading
};