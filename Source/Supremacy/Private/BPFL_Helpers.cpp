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

TArray<uint8> ConvertFloatToBytes(const float Input)
{
	constexpr int32 BufferSize = sizeof Input;
	uint8* Buffer = new uint8[BufferSize];
	memcpy(&Buffer[0], &Input, BufferSize);
	TArray<uint8> Bytes = TArray<uint8>();
	for (int i = 0; i < BufferSize; i++)
	{
		Bytes.Add(Buffer[i]);
	}
	return Bytes;
}
TArray<uint8> ConvertIntToBytes(const int Input)
{
	constexpr int32 BufferSize = sizeof Input;
	uint8* Buffer = new uint8[BufferSize];
	memcpy(&Buffer[0], &Input, BufferSize);
	TArray<uint8> Bytes = TArray<uint8>();
	for (int i = 0; i < BufferSize; i++)
	{
		Bytes.Add(Buffer[i]);
	}
	return Bytes;
}
void UBPFL_Helpers::PackWarMachineMoveUpdate(const uint8 Number, const int X, const int Y, const float Yaw,
	TArray<uint8>& Bytes)
{
	Bytes = TArray<uint8>();
	Bytes.Add(Number);
	Bytes.Append(ConvertIntToBytes(X));
	Bytes.Append(ConvertIntToBytes(Y));
	Bytes.Append(ConvertFloatToBytes(Yaw));
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
