#pragma once

#include "Types/Faction.h"

#include "User.generated.h"

USTRUCT(BlueprintType)
struct FUser
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Role_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFactionServer Faction;
};