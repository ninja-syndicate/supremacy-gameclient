#pragma once

#include "BPFL_Helpers.h"
#include "MapEventMessage.h"
#include "MapEventType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapEventLandmine.generated.h"

USTRUCT() 
struct FMapEventLandmineActivation {
	GENERATED_BODY()
public:
	int32 LandmineID;
	FIntPoint Location;
	int32 GameTimeInMS;

	FMapEventLandmineActivation(): LandmineID(0), Location(FIntPoint(0, 0)), GameTimeInMS(0) {}
	FMapEventLandmineActivation(const int32 ID, const FIntPoint Location, const int32 GameTimeInMS) : LandmineID(ID), Location(Location), GameTimeInMS(GameTimeInMS) {}
};

USTRUCT() 
struct FMapEventLandmineActivations : public FMapEventMessage  {
	GENERATED_BODY()
public:
	uint8 Faction;

	TArray<FMapEventLandmineActivation> Landmines;

	FMapEventLandmineActivations(): Faction(0) {}
	explicit FMapEventLandmineActivations(const int32 Faction) : Faction(Faction) {}
	
	virtual TArray<uint8> Pack() const override
	{
		if (Landmines.IsEmpty()) return {};
		
		TArray<uint8> Bytes = TArray<uint8>();
		Bytes.Emplace(static_cast<uint8>(EMapEventType::MapEventType_LandmineActivations));
		Bytes.Emplace(static_cast<uint8>(Landmines.Num()));
		Bytes.Emplace(Faction);

		const int32 CurrentTimeMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		for (const auto [LandmineID, Location, GameTimeInMS] : Landmines) 
		{
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(LandmineID));
			const uint16 TimeOffset = static_cast<int16>(CurrentTimeMS - GameTimeInMS);
			Bytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(TimeOffset));
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(Location.X));
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(Location.Y));
		}
		
		return Bytes;
	}

	virtual void Clear() override
	{
		Landmines.Empty();
	}
	
};

USTRUCT() 
struct SUPREMACY_API FMapEventLandmineExplosion {
	GENERATED_BODY()
public:
	int32 LandmineID;
	int32 GameTimeInMS;

	FMapEventLandmineExplosion() : LandmineID(0), GameTimeInMS(0) {}
	FMapEventLandmineExplosion(const int32 LandmineID, const int32 GameTimeInMS) : LandmineID(LandmineID), GameTimeInMS(GameTimeInMS) {}
};

USTRUCT() 
struct FMapEventLandmineExplosions : public FMapEventMessage  {
	GENERATED_BODY()
public:
	TArray<FMapEventLandmineExplosion> Landmines;

	virtual TArray<uint8> Pack() const override
	{
		if (Landmines.IsEmpty()) return {};
		
		TArray<uint8> Bytes = TArray<uint8>();
		Bytes.Emplace(static_cast<uint8>(EMapEventType::MapEventType_LandmineExplosions));
		Bytes.Emplace(static_cast<uint8>(Landmines.Num()));

		const int32 CurrentTimeMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		for (const auto [LandmineID, GameTimeInMS] : Landmines) 
		{
			Bytes.Append(UBPFL_Helpers::ConvertIntToBytes(LandmineID));
			const uint16 TimeOffset = static_cast<int16>(CurrentTimeMS - GameTimeInMS);
			Bytes.Append(UBPFL_Helpers::ConvertUInt16ToBytes(TimeOffset));
		}
		
		return Bytes;
	}

	virtual void Clear() override
	{
		Landmines.Empty();
	}
};
