#pragma once

#include "BPFL_Helpers.h"
#include "MapEventMessage.h"
#include "MapEventType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapEventTheHive.generated.h"

USTRUCT() 
struct SUPREMACY_API FMapEventHiveChange {
	GENERATED_BODY()
public:
	uint16 HexID;
	int32 GameTimeInMS;

	FMapEventHiveChange() : HexID(0), GameTimeInMS(0) {}
	FMapEventHiveChange(const uint16 HexID, const int32 GameTimeInMS) : HexID(HexID), GameTimeInMS(GameTimeInMS) {}
};

USTRUCT() 
struct SUPREMACY_API FMapEventHiveChanges : public FMapEventMessage {
	GENERATED_BODY()
public:
	EMapEventType MapEventType;
	TArray<FMapEventHiveChange> Changes;

	FMapEventHiveChanges(): MapEventType(EMapEventType::MapEventType_HiveHexRaised) {}
	explicit FMapEventHiveChanges(const EMapEventType MapEventType) : MapEventType(MapEventType) {}

	virtual TArray<uint8> Pack(const UObject* WorldContextObject) const override
	{
		if (Changes.IsEmpty()) return {};
		
		TArray<uint8> Bytes = TArray<uint8>();
		Bytes.Emplace(static_cast<uint8>(MapEventType));
		Bytes.Emplace(static_cast<uint8>(Changes.Num()));

		const int32 CurrentTimeMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(WorldContextObject) * 1000);
		for (const auto [HexID, GameTimeInMS] : Changes) 
		{
			Bytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(HexID));
			
			const int32 Offset = CurrentTimeMS - GameTimeInMS;
			const uint8 TimeOffset = static_cast<uint8>(Offset > 255 ? 255 : Offset); // since tick is 0.25s time offset should never go past 250
			Bytes.Emplace(TimeOffset);
		}
		
		return Bytes;
	}

	virtual void Clear() override
	{
		Changes.Empty();
	}
};

USTRUCT() 
struct SUPREMACY_API FMapEventHiveChangesRaised : public FMapEventHiveChanges
{
	GENERATED_BODY()

	FMapEventHiveChangesRaised() : FMapEventHiveChanges(EMapEventType::MapEventType_HiveHexRaised) {}
};

USTRUCT() 
struct SUPREMACY_API FMapEventHiveChangesLowered: public FMapEventHiveChanges
{
	GENERATED_BODY()

	FMapEventHiveChangesLowered() : FMapEventHiveChanges(EMapEventType::MapEventType_HiveHexLowered) {}
};