#pragma once

#include "User.h"

#include "PayloadLogin.generated.h"

USTRUCT(BlueprintType)
struct FLoginRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Email;
	UPROPERTY()
	FString Password;
};

USTRUCT(BlueprintType)
struct FLoginResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FUser User;
};
