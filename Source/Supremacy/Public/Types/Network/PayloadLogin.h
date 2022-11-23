#pragma once

#include "User.h"

#include "PayloadLogin.generated.h"

USTRUCT(BlueprintType)
struct FLoginEmailRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Email;
	UPROPERTY()
	FString Password;
	UPROPERTY()
	bool Is_External;
};

USTRUCT(BlueprintType)
struct FLoginTokenRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Token;
};

USTRUCT(BlueprintType)
struct FLoginEmailResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FUser User;
	UPROPERTY();
	FString Issue_Token;
};
USTRUCT(BlueprintType)
struct FLoginTokenResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FUser User;
	UPROPERTY();
	FString Token;
};

USTRUCT(BlueprintType)
struct FErrorMessage
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Message;
	UPROPERTY();
	FString Error_Code;
};