#pragma once

#include "CoreMinimal.h"
#include "StaticData/StaticData.h"
#include "Engine/EngineTypes.h"
#include "Chaos/ChaosEngineInterface.h"
#include "SupremacyFunctionLibrary.generated.h"

// @note - Not all custom channels/types are listed.
/** Supremacy Trace Channels */
#define TraceChannel_Damageable ECollisionChannel::ECC_GameTraceChannel3
#define TraceChannel_Level ECollisionChannel::ECC_GameTraceChannel4
#define TraceChannel_Ground ECollisionChannel::ECC_GameTraceChannel7

/** Supremacy Physical Surface Types */
#define SurfaceType_Sand EPhysicalSurface::SurfaceType3
#define SurfaceType_Energy EPhysicalSurface::SurfaceType5

UCLASS()
class SUPREMACY_API USupremacyFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(Category = "Supremacy Function Library", BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TSubclassOf<class UDamageType> ConvertToDamageType(const UObject* WorldContextObject, const uint8 DamageType);

	UFUNCTION(Category = "Supremacy Function Library", BlueprintPure, meta = ( WorldContext = "WorldContextObject"))
	static UStaticData* GetStaticData(const UObject* WorldContextObject);
};