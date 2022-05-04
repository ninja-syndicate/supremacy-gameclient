// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Helpers.h"
#include "Components/ActorComponent.h"

#include <string>

#include "Windows/WindowsPlatformApplicationMisc.h"

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

void UBPFL_Helpers::PackWarMachineUpdate(const uint8 Number, const int X, const int Y, const int Yaw, const int Health, const int Shield, const int Energy, 
	const TArray<bool> DiffArray, TArray<uint8>& Bytes)
{
	Bytes = TArray<uint8>();
	Bytes.Emplace(Number);
	Bytes.Emplace(PackBooleansIntoByte(DiffArray));

	if (DiffArray[0])
	{
		Bytes.Append(ConvertIntToBytes(X));
		Bytes.Append(ConvertIntToBytes(Y));
		Bytes.Append(ConvertIntToBytes(Yaw));
	}
	if (DiffArray[1])
		Bytes.Append(ConvertIntToBytes(Health));
	if (DiffArray[2])
		Bytes.Append(ConvertIntToBytes(Shield));
	if (DiffArray[3])
		Bytes.Append(ConvertIntToBytes(Energy));
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

uint8 UBPFL_Helpers::PackBooleansIntoByte(const TArray<bool> Booleans)
{
	uint8 Byte = 0;
	for (int i = 0; i < Booleans.Num(); ++i)
	{
		if (Booleans[i])
			Byte |= 1 << i;
	}
	return Byte;
}

TArray<bool> UBPFL_Helpers::UnpackBooleansFromByte(const uint8 Byte)
{
	TArray<bool> booleans = TArray<bool>();
	booleans.Init(false, 8);
	for (int i = 0; i < 8; ++i)
		booleans[i] = (Byte & (1 << i)) != 0;
	return booleans;
}

FColor UBPFL_Helpers::HexToColor(const FString HexString)
{
	return FColor::FromHex(HexString);
}

FString UBPFL_Helpers::ColorToHex(const FColor Color)
{
	return Color.ToHex();
}

ECollisionResponse UBPFL_Helpers::GetComponentsCollisionResponseToChannel(AActor* Actor, ECollisionChannel Channel)
{
	// Return ignore response if the actor is not valid.
	if (!IsValid(Actor))
		return ECollisionResponse::ECR_Ignore;

	return Actor->GetComponentsCollisionResponseToChannel(Channel);
}

FString UBPFL_Helpers::CopyMapDetailsToClipboard(const FMapDetails MapDetails)
{
	FString Text =R""""(  {
    "Name",
    {
      "Name",
      "ImageURL",
      Width, Height,
      CellsX, CellsY,
      PixelLeft, PixelTop,
      {DisabledCells}
    },
  },)"""";
	Text = Text.Replace(TEXT("Name"), ToCStr(MapDetails.Name));
	Text = Text.Replace(TEXT("ImageURL"), ToCStr(MapDetails.ImageURL));
	Text = Text.Replace(TEXT("Width"), ToCStr(FString::FromInt(MapDetails.Width)));
	Text = Text.Replace(TEXT("Height"), ToCStr(FString::FromInt(MapDetails.Height)));
	Text = Text.Replace(TEXT("CellsX"), ToCStr(FString::FromInt(MapDetails.CellsX)));
	Text = Text.Replace(TEXT("CellsY"), ToCStr(FString::FromInt(MapDetails.CellsY)));
	Text = Text.Replace(TEXT("PixelLeft"), ToCStr(FString::FromInt(MapDetails.PixelLeft)));
	Text = Text.Replace(TEXT("PixelTop"), ToCStr(FString::FromInt(MapDetails.PixelTop)));

	FString DisabledCells = "";
	for (const int DisabledCell : MapDetails.DisabledCells)
	{
		if (!DisabledCells.IsEmpty()) DisabledCells += ",";
		DisabledCells += FString::FromInt(DisabledCell);
	}
	
	Text = Text.Replace(TEXT("DisabledCells"), ToCStr(DisabledCells));
	
	FWindowsPlatformApplicationMisc::ClipboardCopy(*Text);
	return Text;
}

void UBPFL_Helpers::ForceDestroyComponent(UActorComponent* ActorComponent)
{
    if (IsValid(ActorComponent))
    {
		ActorComponent->DestroyComponent();
    }
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BPFL_Helpers: Failed to force destroy the actor component!"));
	}
}

void UBPFL_Helpers::SetLockPhysiscs(UStaticMeshComponent* Mesh, bool LockTranslationX, bool LockTranslationY, bool LockTranslationZ, bool LockRotationX, bool LockRotationY, bool LockRotationZ)
{
	Mesh->BodyInstance.bLockXTranslation = LockTranslationX;
	Mesh->BodyInstance.bLockYTranslation = LockTranslationY;
	Mesh->BodyInstance.bLockZTranslation = LockTranslationZ;
	Mesh->BodyInstance.bLockXRotation = LockRotationX;
	Mesh->BodyInstance.bLockYRotation = LockRotationY;
	Mesh->BodyInstance.bLockZRotation = LockRotationZ;
	Mesh->BodyInstance.CreateDOFLock();
}
