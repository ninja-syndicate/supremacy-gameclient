#pragma once

#include "CoreMinimal.h"
#include "AvoidanceFlags.generated.h"

UENUM(BlueprintType)
namespace EAvoidanceFlags
{
	enum EAvoidanceFlags
	{
		AvoidanceSubsystem_None   = 0,
		AvoidanceSubsystem_Player = 1 << 0,
		AvoidanceSubsystem_AI     = 1 << 1
	};
}