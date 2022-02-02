// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Helpers.h"

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
