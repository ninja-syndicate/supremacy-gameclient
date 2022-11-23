#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Http.h"
#include "Types/Network/PayloadLogin.h"
#include "AuthSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAuth, Log, All);



/**
 * Authentication with Xsyn
 */
UCLASS(Config=Game)
class SUPREMACY_API UAuthSubsystem final : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Config)
	FString APIEndpoint;
	
	FUser CurrentUser;
	FString CurrentToken;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Getters
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Auth Subsystem")
	void GetUser(bool& Valid, FUser& User) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Auth Subsystem")
	void GetToken(bool& Valid, FString& Token) const;
	
	// Delegates
	
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FLoginRequestComplete, FUser, User, FString, Token);
	UPROPERTY()
	FLoginRequestComplete LoginRequestComplete;
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FLoginRequestError, FString, Message);
	UPROPERTY()
	FLoginRequestError LoginRequestError;

	// Login functions
	
	UFUNCTION(BlueprintCallable, Category="Auth Subsystem")
	void LoginEmail(const FString& Email, const FString& Password, const FLoginRequestComplete OnComplete, const FLoginRequestError OnError);
	
	UFUNCTION(BlueprintCallable, Category="Auth Subsystem")
	void LoginToken(const FString& Token, const FLoginRequestComplete OnComplete, const FLoginRequestError OnError);

protected:
	FHttpModule* Http;
	void OnLoginRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool Success) const;
};