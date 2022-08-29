#pragma once

#include "CoreMinimal.h"
#include "MapEventMessage.generated.h"

USTRUCT() 
struct SUPREMACY_API FMapEventMessage {
	GENERATED_BODY()
public:
	virtual ~FMapEventMessage() = default;
	virtual TArray<uint8> Pack() const { return {}; }
	virtual void Clear() {}
};
