#pragma once

#include "CoreMinimal.h"
#include "MapEventAirstrikeExplosions.h"
#include "MapEventLandmine.h"
#include "MapEventMessage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapEventMessages.generated.h"

UCLASS(BlueprintType) 
class SUPREMACY_API UMapEventMessages final : public UObject {
	GENERATED_BODY()

	TArray<FMapEventMessage*> Messages;

	FMapEventAirstrikeExplosions AirstrikeExplosions;
	
	TArray<FMapEventLandmineActivations> LandmineActivations;
	FMapEventLandmineExplosions LandmineExplosions;
	int32 NextLandmineID = 0;

	UMapEventMessages()
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

			// Only sent straight to frontend clients
			&AirstrikeExplosions,
		};
	}
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	TArray<uint8> Pack(const UObject* WorldContextObject) const
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		
		TArray<uint8> Bytes = TArray<uint8>();
		uint8 MessageCount = 0;
		for (const FMapEventMessage* Message : Messages)
		{
			TArray<uint8> MessagedPacked = Message->Pack(World);
			if (MessagedPacked.Num() == 0) continue;
			Bytes.Append(MessagedPacked);
			MessageCount++;
		}

		if (MessageCount == 0) return {};
		Bytes.Insert(MessageCount, 0);
		
		return Bytes;
	}

	UFUNCTION(BlueprintCallable)
	void Clear() const
	{
		for (FMapEventMessage* Message : Messages)
			Message->Clear();
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
};