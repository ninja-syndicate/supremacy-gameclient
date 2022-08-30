#pragma once

#include "CoreMinimal.h"
#include "NetMessageType.generated.h"

UENUM(BlueprintType)
enum ENetMessageType
{
	NetMessageType_Default UMETA(DisplayName = "Default", ToolTip="Default JSON Message"),
	NetMessageType_Tick UMETA(DisplayName = "Tick"),
};
