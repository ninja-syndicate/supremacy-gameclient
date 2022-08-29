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
			&AirstrikeExplosions,
			&LandmineActivations[0], &LandmineActivations[1], &LandmineActivations[2],
			&LandmineExplosions,
		};
	}.
	
public:
	UFUNCTION(BlueprintPure)
	TArray<uint8> Pack() const
	{
		TArray<uint8> Bytes = TArray<uint8>();
		uint8 MessageCount = 0;
		for (const FMapEventMessage* Message : Messages)
		{
			TArray<uint8> MessagedPacked = Message->Pack();
			if (MessagedPacked.Num() == 0) continue;
			Bytes.Append(MessagedPacked);
			MessageCount++;
		}

		if (MessageCount == 0) return {};
		Bytes.Insert(static_cast<uint8>(MessageCount), 0);
		
		return Bytes;
	}

	UFUNCTION(BlueprintCallable)
	void Clear() const
	{
		for (FMapEventMessage* Message : Messages)
			Message->Clear();
	}

	UFUNCTION(BlueprintCallable)
	void AirstrikeExplosion(const FIntPoint Location)
	{
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		AirstrikeExplosions.Locations.Add(FMapEventAirstrikeExplosion(Location, TimeInMS));
	}
	
	UFUNCTION(BlueprintCallable)
	int32 LandmineActivation(const FIntPoint Location, const uint8 Faction)
	{
		if (Faction == 0 || Faction > 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("LandmineActivation - invalid faction, must be a number between 1-3"));
			return 0;
		}
		const int32 LandmineID = NextLandmineID++;
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		LandmineActivations[Faction-1].Landmines.Add(FMapEventLandmineActivation(LandmineID, Location, TimeInMS));
		return LandmineID;
	}

	UFUNCTION(BlueprintCallable)
	void LandmineExplosion(const int32 LandmineID)
	{
		const int32 TimeInMS = FMath::FloorToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GEngine->GetWorld()) / 1000);
		LandmineExplosions.Landmines.Add(FMapEventLandmineExplosion(LandmineID, TimeInMS));
	}
};