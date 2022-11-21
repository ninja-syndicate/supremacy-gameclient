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

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(Config)
	FString APIEndpoint;

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FLoginRequestComplete, bool, Success, FUser, User);
	UPROPERTY()
	FLoginRequestComplete LoginRequestComplete;
	UFUNCTION(BlueprintCallable, Category="Auth Subsystem")
	void Login(const FString& Email, const FString& Password, const FLoginRequestComplete OnComplete);

protected:
	FHttpModule* Http;
	void OnLoginRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool Success) const;
};