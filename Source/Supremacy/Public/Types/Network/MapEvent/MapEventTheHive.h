#pragma once

#include "BPFL_Helpers.h"
#include "MapEventMessage.h"
#include "MapEventType.h"
#include "Containers/Queue.h"
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
	TQueue<FMapEventHiveChange> Changes;

	FMapEventHiveChanges(): MapEventType(EMapEventType::MapEventType_HiveHexRaised) {}
	explicit FMapEventHiveChanges(const EMapEventType MapEventType) : MapEventType(MapEventType) {}

	virtual TArray<uint8> Pack(const UObject* WorldContextObject) override
	{
		if (Changes.IsEmpty()) return {};

		uint16 Count = 0;
		
		TArray<uint8> Bytes = TArray<uint8>();
		Bytes.Emplace(static_cast<uint8>(MapEventType));

		const int32 CurrentTimeMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(WorldContextObject) * 1000);

		FMapEventHiveChange Change;
		TArray<uint8> ChangesBytes = TArray<uint8>();
		while (Changes.Dequeue(Change))
		{
			ChangesBytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(Change.HexID));
			
			const int32 Offset = CurrentTimeMS - Change.GameTimeInMS;
			const uint8 TimeOffset = static_cast<uint8>(Offset > 255 ? 255 : Offset); // since tick is 0.25s time offset should never go past 250
			ChangesBytes.Emplace(TimeOffset);

			Count++;
		}

		Bytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(Count));
		Bytes.Append(ChangesBytes);
		
		return Bytes;
	}
};
template<>
struct TStructOpsTypeTraits< FMapEventHiveChanges > : TStructOpsTypeTraitsBase2< FMapEventHiveChanges >
{
	enum
	{
		WithCopy = false
	 };
};
