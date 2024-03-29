#pragma once

#include "CoreMinimal.h"
#include "MapEventAirstrikeExplosions.h"
#include "MapEventLandmine.h"
#include "MapEventMessage.h"
#include "MapEventTheHive.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapEventManager.generated.h"

UCLASS(BlueprintType) 
class SUPREMACY_API UMapEventManager final : public UObject {
	GENERATED_BODY()

	TArray<FMapEventMessage*> Messages;

	FMapEventAirstrikeExplosions AirstrikeExplosions;
	
	TArray<FMapEventLandmineActivations> LandmineActivations;
	FMapEventLandmineExplosions LandmineExplosions;
	int32 NextLandmineID = 0;

	FMapEventHiveChanges HiveChangesLowered = FMapEventHiveChanges(EMapEventType::MapEventType_HiveHexLowered);
	FMapEventHiveChanges HiveChangesRaised = FMapEventHiveChanges(EMapEventType::MapEventType_HiveHexRaised);

	UMapEventManager()
	{
		LandmineActivations = {
			FMapEventLandmineActivations(1),
			FMapEventLandmineActivations(2),
			FMapEventLandmineActivations(3)
		};

		Messages = {
			// Will be unpacked and saved on server
			&LandmineActivations[0], &LandmineActivations[1], &LandmineActivations[2],
			&LandmineExplosions,

			&HiveChangesRaised,
			&HiveChangesLowered,

			// Only sent straight to frontend clients
			&AirstrikeExplosions,
		};
	}
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", ToolTip="Packs all current map events to byte array, clearing them at the same time."))
	TArray<uint8> Pack(const UObject* WorldContextObject) const
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		
		TArray<uint8> Bytes = TArray<uint8>();
		uint8 MessageCount = 0;
		for (FMapEventMessage* Message : Messages)
		{
			TArray<uint8> MessagedPacked = Message->Pack(World);
			if (MessagedPacked.Num() == 0) continue;
			Bytes.Append(MessagedPacked);
			MessageCount++;
		}
		
		Bytes.Insert(MessageCount, 0);
		
		return Bytes;
	}

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	void AirstrikeExplosion(const UObject* WorldContextObject, const FIntPoint Location)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
			
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(World) * 1000);
		AirstrikeExplosions.Locations.Add(FMapEventAirstrikeExplosion(Location, TimeInMS));
	}
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	int32 LandmineActivation(const UObject* WorldContextObject, const FIntPoint Location, const uint8 Faction)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		
		if (Faction == 0 || Faction > 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("LandmineActivation - invalid faction, must be a number between 1-3"));
			return 0;
		}
		const int32 LandmineID = NextLandmineID++;
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(World) * 1000);
		LandmineActivations[Faction-1].Landmines.Add(FMapEventLandmineActivation(LandmineID, Location, TimeInMS));
		return LandmineID;
	}

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	void LandmineExplosion(const UObject* WorldContextObject, const int32 LandmineID)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(World) * 1000);
		LandmineExplosions.Landmines.Add(FMapEventLandmineExplosion(LandmineID, TimeInMS));
	}

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	void HiveMapChange(const UObject* WorldContextObject, const int32 HexID, const bool Raised)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(World) * 1000);
		const FMapEventHiveChange Change = FMapEventHiveChange(static_cast<uint16>(HexID), TimeInMS);
		if (Raised)
			HiveChangesRaised.Changes.Enqueue(Change);
		else
			HiveChangesLowered.Changes.Enqueue(Change);
	}
};