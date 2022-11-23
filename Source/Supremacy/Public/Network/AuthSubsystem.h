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
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	// Delegates
	
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FLoginRequestComplete, FUser, User, FString, Token);
	UPROPERTY()
	FLoginRequestComplete LoginRequestComplete;
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FLoginRequestError, FString, Message);
	UPROPERTY()
	FLoginRequestError LoginRequestError;

	// Login functions
	
	UFUNCTION(BlueprintCallable, Category="Auth Subsystem", meta=(ToolTip="Login with email and password."))
	void LoginEmail(const FString& Email, const FString& Password, const FLoginRequestComplete OnComplete, const FLoginRequestError OnError);

	UFUNCTION(BlueprintCallable, Category="Auth Subsystem", meta=(ToolTip="Attempt auto login with saved token from previous login."))
	void LoginToken(const FLoginRequestComplete OnComplete, const FLoginRequestError OnError);

	UFUNCTION(BlueprintCallable, Category="Auth Subsystem", meta=(ToolTip="Sends logout request to server and clears token."))
	void Logout() const;

protected:
	FHttpModule* Http;
	void OnLoginRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool Success) const;

private:
	void SaveToken(const FString& Token) const;
	void ClearToken() const;
	
	bool HasInvalidAPIEndpoint() const;
};
