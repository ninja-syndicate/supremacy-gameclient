// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_Helpers.h"

void UBPFL_Helpers::ConvertStringToBytes(const FString String, TArray<uint8> &Bytes)
{
	const int32 BufferSize = String.Len();
	uint8* Buffer = new uint8[String.Len()];
	StringToBytes(String, Buffer, BufferSize);
	Bytes = TArray<uint8>();
	for (int i = 0; i < BufferSize; i++) {
		Bytes.Add(Buffer[i]);
	}
}
