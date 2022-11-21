#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Chaos/ChaosEngineInterface.h"
#include "SupremacyTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSupremacy, Log, All);

// @note - Not all custom channels/types are listed.
/** Supremacy Trace Channels */
#define TraceChannel_Damageable ECollisionChannel::ECC_GameTraceChannel3
#define TraceChannel_Level ECollisionChannel::ECC_GameTraceChannel4
#define TraceChannel_Ground ECollisionChannel::ECC_GameTraceChannel7

/** Supremacy Physical Surface Types */
#define SurfaceType_Sand EPhysicalSurface::SurfaceType3
#define SurfaceType_Energy EPhysicalSurface::SurfaceType5

UCLASS()
class SUPREMACY_API USupremacyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(Category = "Supremacy Function Library", BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TSubclassOf<class UDamageType> ConvertToDamageType(const UObject* WorldContextObject, uint8 DamageType);
};