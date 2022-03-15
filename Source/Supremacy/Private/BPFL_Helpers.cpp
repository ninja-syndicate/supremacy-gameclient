// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Helpers.h"
#include "Kismet/KismetSystemLibrary.h"

void UBPFL_Helpers::ParseNetMessage(const TArray<uint8> Bytes, uint8& Type, FString& Message)
{
	Type = Bytes[0];
	if (Bytes.Num() > 1)
	{
		FString Broken = BytesToString(&Bytes[1],  Bytes.Num()-1);
		for (int i = 0; i < Broken.Len(); i++)
		{
			const TCHAR c = Broken[i] - 1;
			Message.AppendChar(c);
		}
	}
}

TArray<uint8> ConvertIntToBytes(const int Input)
{
	TArray<uint8> Bytes = TArray<uint8>();
	Bytes.Emplace((Input >> 24) & 0xFF);
	Bytes.Emplace((Input >> 16) & 0xFF);
	Bytes.Emplace((Input >> 8) & 0xFF);
	Bytes.Emplace((Input >> 0) & 0xFF);
	return Bytes;
}
void UBPFL_Helpers::PackWarMachineUpdate(const uint8 Number, const int X, const int Y, const int Yaw, const int Health, const int Shield, const uint8 SyncByte, 
	TArray<uint8>& Bytes)
{
	Bytes = TArray<uint8>();
	Bytes.Emplace(Number);
	Bytes.Emplace(SyncByte);
	if (SyncByte >= 100)
	{
		Bytes.Append(ConvertIntToBytes(X));
		Bytes.Append(ConvertIntToBytes(Y));
		Bytes.Append(ConvertIntToBytes(Yaw));
	}
	if (SyncByte == 1 || SyncByte == 11 || SyncByte == 101 || SyncByte == 111)
	{
		Bytes.Append(ConvertIntToBytes(Health));
	}
	if (SyncByte == 10 || SyncByte == 11 || SyncByte == 110 || SyncByte == 111)
	{
		Bytes.Append(ConvertIntToBytes(Shield));
	}
}

void UBPFL_Helpers::ConvertStringToBytes(const FString String, TArray<uint8> &Bytes)
{
	const int32 BufferSize = String.Len();
	uint8* Buffer = new uint8[String.Len()];
	StringToBytes(String, Buffer, BufferSize);
	Bytes = TArray<uint8>();
	for (int i = 0; i < BufferSize; i++)
	{
		Bytes.Add(Buffer[i]);
	}
}

void UBPFL_Helpers::ConvertBytesToString(const TArray<uint8> Bytes, FString& String)
{
	FString Broken = BytesToString(&Bytes[0],  Bytes.Num());
	for (int i = 0; i < Broken.Len(); i++)
	{
		const TCHAR c = Broken[i] - 1;
		String.AppendChar(c);
	}
}

FColor UBPFL_Helpers::HexToColor(const FString HexString)
{
	return FColor::FromHex(HexString);
}

FString UBPFL_Helpers::ColorToHex(const FColor Color)
{
	return Color.ToHex();
}

static bool GetGroundLocation(const UObject* WorldContextObject, FVector Origin, FVector UpAxis, FVector& OutLocation)
{
	FHitResult HitResult;
	FVector OriginHigh = Origin + UpAxis * 1000000.f;
	FVector OriginLow = Origin + UpAxis * -1000000.f;
	ECollisionChannel LevelChannel = ECC_GameTraceChannel4;

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		// fatal;
		UE_LOG(LogTemp, Warning, TEXT("Invalid world context"));
		return false;
	}
	bool IsHit = World->LineTraceSingleByChannel(HitResult, OriginHigh, OriginLow, LevelChannel);
	if (!IsHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level trace failed. Landscape probably doesn't have collision channel set up properly."));
		return false;
	}
	OutLocation = HitResult.Location;
	return true;
}

bool UBPFL_Helpers::GetNearestEmptyLocation(
	const UObject* WorldContextObject,
	FVector Origin,
	FVector ForwardAxis,
	FVector UpAxis,
	float DesiredRadius,
	float MaxDistance,
	TArray<AActor*> ActorsToIgnore,
	FVector& OutLocation,
	bool bCheckGround)
{
	// Object types to consider.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypeQueries.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> OverlappingActors;

	FVector TestLocation = Origin;
	if (bCheckGround)
	{
		bool IsSuccess = GetGroundLocation(WorldContextObject, Origin, UpAxis, TestLocation);
		UE_LOG(LogTemp, Warning, TEXT("1. Ground Location %f %f %f"), TestLocation.X, TestLocation.Y, TestLocation.Z);
		if (!IsSuccess)
		{
			return false;
		}
	}

	// Try the given origin to see if it is empty.
	UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, TestLocation, DesiredRadius, ObjectTypeQueries, nullptr, ActorsToIgnore, OverlappingActors);
	if (OverlappingActors.IsEmpty())
	{
		OutLocation = TestLocation;
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Should get to here"));

	// Otherwise, try different directions of increasing distance from the origin.
	const int NumDirections = 8;
	for (float CurrentTestDistance = 500; CurrentTestDistance <= MaxDistance; CurrentTestDistance += 1000)
	{
		for (int i = 0; i < NumDirections; ++i)
		{
			const float CurrentAngle = 360.f * (i / static_cast<float>(NumDirections));
			const FVector CurrentDirection = ForwardAxis.RotateAngleAxis(CurrentAngle, UpAxis);
			const FVector NewOrigin = Origin + CurrentDirection * CurrentTestDistance;

			TestLocation = NewOrigin;
			if (bCheckGround)
			{
				bool IsSuccess = GetGroundLocation(WorldContextObject, NewOrigin, UpAxis, TestLocation);
				if (!IsSuccess)
				{
					return false;
				}
			}
			UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, TestLocation, DesiredRadius, ObjectTypeQueries, nullptr, ActorsToIgnore, OverlappingActors);
			if (OverlappingActors.IsEmpty())
			{
				UE_LOG(LogTemp, Warning, TEXT("This must be called... but how?"));
				OutLocation = TestLocation;
				return true;
			}
		}
	}
	OutLocation = FVector::ZeroVector;
	return false;
}