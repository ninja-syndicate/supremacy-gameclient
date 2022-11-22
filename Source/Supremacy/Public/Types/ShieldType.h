#pragma once

#include "CoreMinimal.h"
#include "ShieldType.generated.h"

UENUM(BlueprintType)
enum class EShieldType : uint8
{
	ShieldType_Orb = 0 UMETA(DisplayName = "Orb Shield"),
	ShieldType_Form UMETA(DisplayName = "Form Shield"),
};

const TMap<FGuid, EShieldType> GuidToEShieldType = {
	{ FGuid("d318e7cd-166a-406a-b5cc-6fddea622876"), EShieldType::ShieldType_Orb },
	{ FGuid("b209a593-f0a0-4df9-bc8d-f6af8bab4362"), EShieldType::ShieldType_Form },
};
