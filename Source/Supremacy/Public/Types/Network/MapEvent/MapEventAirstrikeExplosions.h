#pragma once

#include "BPFL_Helpers.h"
#include "MapEventMessage.h"
#include "MapEventType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapEventAirstrikeExplosions.generated.h"

USTRUCT() 
struct SUPREMACY_API FMapEventAirstrikeExplosion {
	GENERATED_BODY()
public:
	FIntPoint Location;
	int32 GameTimeInMS;

	FMapEventAirstrikeExplosion() : Location(0, 0), GameTimeInMS(0) {}
	FMapEventAirstrikeExplosion(const FIntPoint Location, const int32 GameTimeInMS) : Location(Location), GameTimeInMS(GameTimeInMS) {}
};

USTRUCT() 
struct SUPREMACY_API FMapEventAirstrikeExplosions : public FMapEventMessage {
	GENERATED_BODY()
public:
	TArray<FMapEventAirstrikeExplosion> Locations;

	virtual TArray<uint8> Pack() const override
	{
		if (Locations.IsEmpty()) return {};
		
		TArray<uint8> Bytes = TArray<uint8>();
		Bytes.Emplace(static_cast<uint8>(EMapEventType::MapEventType_AirstrikeExplosions));
		Bytes.Emplace(static_cast<uint8>(Locations.Num()));

		const int32 CurrentTimeMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		for (const auto [Location, GameTimeInMS] : Locations) 
		{
			const uint16 TimeOffset = static_cast<int16>(CurrentTimeMS - GameTimeInMS);
			Bytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(TimeOffset));
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(Location.X));
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(Location.Y));
		}
		
		return Bytes;
	}

	virtual void Clear() override
	{
		Locations.Empty();
	}
};
