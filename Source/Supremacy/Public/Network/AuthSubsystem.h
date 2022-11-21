// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Http.h"
#include "AuthSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAuth, Log, All);

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
	FString Email;
	UPROPERTY()
	FString ID;
};

/**
 * Authentication with Xsyn
 */
UCLASS(Config=Game)
class SUPREMACY_API UAuthSubsystem final : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="Auth Subsystem")
	void Login(const FString& Email, const FString& Password) const;

	UPROPERTY(Config)
	FString APIEndpoint;
	
	// DECLARE_DELEGATE_OneParam(FLoginRequestComplete, FLoginResponse)
	// UPROPERTY(BlueprintAssignable, Category="Auth Subsystem")
	// FLoginRequestComplete LoginRequestComplete;
protected:
	FHttpModule* Http;
	void OnLoginRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);
};