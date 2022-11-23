#include "Network/AuthSubsystem.h"
#include "JsonObjectConverter.h"
#include "Core/Game/SupremacySaveGame.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogAuth);

void UAuthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Http = &FHttpModule::Get();

	if (APIEndpoint.IsEmpty())
		UE_LOG(LogAuth, Warning, TEXT("Auth Subsystem API Endpoint is unset."));
}

void UAuthSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAuthSubsystem::LoginEmail(const FString& Email, const FString& Password, const FLoginRequestComplete OnComplete,
                                const FLoginRequestError OnError)
{
	LoginRequestComplete = OnComplete;
	LoginRequestError = OnError;

	if (HasInvalidAPIEndpoint())
		return;

	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UAuthSubsystem::OnLoginRequestComplete);
	Request->SetURL(APIEndpoint + "/auth/email");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString JsonString;
	FLoginEmailRequest Payload;
	Payload.Email = Email;
	Payload.Password = Password;
	Payload.Is_External = true;
	FJsonObjectConverter::UStructToJsonObjectString(Payload, JsonString);
	Request->SetContentAsString(JsonString);

	Request->ProcessRequest();
}

void UAuthSubsystem::LoginToken(const FLoginRequestComplete OnComplete, const FLoginRequestError OnError)
{
	LoginRequestComplete = OnComplete;
	LoginRequestError = OnError;

	if (HasInvalidAPIEndpoint())
		return;

	// Get token
	FString Token;
	if (const USupremacySaveGame* LoadedGame = Cast<USupremacySaveGame>(
		UGameplayStatics::LoadGameFromSlot("SaveGame", 0)))
	{
		Token = *LoadedGame->Token;
	}

	if (Token.IsEmpty())
	{
		bool _ = LoginRequestError.ExecuteIfBound("No Saved Token");
		return;
	}

	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	Request->OnProcessRequestComplete().BindUObject(this, &UAuthSubsystem::OnLoginRequestComplete);
	Request->SetURL(APIEndpoint + "/auth/token");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString JsonString;
	FLoginTokenRequest Payload;
	Payload.Token = Token;
	FJsonObjectConverter::UStructToJsonObjectString(Payload, JsonString);
	Request->SetContentAsString(JsonString);
	
	Request->ProcessRequest();
}

void UAuthSubsystem::Logout() const
{
	// Get token
	FString Token;
	if (const USupremacySaveGame* LoadedGame = Cast<USupremacySaveGame>(
		UGameplayStatics::LoadGameFromSlot("SaveGame", 0)))
	{
		Token = *LoadedGame->Token;
	}
	else
	{
		// No Saved Token
		return;
	}

	// Send logout request to server (invalidates token)
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->SetURL(APIEndpoint + "/auth/logout");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Cookie"), "xsyn-token=" + Token);

	Request->ProcessRequest();

	// Clear token from save game
	ClearToken();
}

void UAuthSubsystem::OnLoginRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response,
                                            const bool Success) const
{
	if (!Success)
	{
		UE_LOG(LogAuth, Warning, TEXT("Login Request Failed"));
		bool _ = LoginRequestError.ExecuteIfBound("Login Request Failed");
		return;
	}

	UE_LOG(LogAuth, Warning, TEXT("%s"), *Response->GetContentAsString());

	if (Response->GetResponseCode() != 200)
	{
		FErrorMessage Payload;
		FJsonObjectConverter::JsonObjectStringToUStruct(*Response->GetContentAsString(), &Payload);
		if (!LoginRequestError.ExecuteIfBound(Payload.Message))
			UE_LOG(LogAuth, Warning, TEXT("Login error and delegate was unbound."));
		return;
	}

	if (Request->GetURL().EndsWith("token"))
	{
		FLoginTokenResponse Payload;
		FJsonObjectConverter::JsonObjectStringToUStruct(*Response->GetContentAsString(), &Payload);
		if (!LoginRequestComplete.ExecuteIfBound(Payload.User, Payload.Token))
			UE_LOG(LogAuth, Warning, TEXT("Login succeced but no delegate was bound."));
	}
	else
	{
		FLoginEmailResponse Payload;
		FJsonObjectConverter::JsonObjectStringToUStruct(*Response->GetContentAsString(), &Payload);
		if (!LoginRequestComplete.ExecuteIfBound(Payload.User, Payload.Issue_Token))
			UE_LOG(LogAuth, Warning, TEXT("Login succeced but no delegate was bound."));
		SaveToken(Payload.Issue_Token);
	}
}

void UAuthSubsystem::SaveToken(const FString& Token) const
{
	if (USupremacySaveGame* SaveGameInstance = Cast<USupremacySaveGame>(UGameplayStatics::CreateSaveGameObject(USupremacySaveGame::StaticClass())))
	{
		SaveGameInstance->Token = Token;
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveGame", 0))
			UE_LOG(LogAuth, Warning, TEXT("Failed to save token."));
	}
}

void UAuthSubsystem::ClearToken() const
{
	if (USupremacySaveGame* SaveGameInstance = Cast<USupremacySaveGame>(UGameplayStatics::CreateSaveGameObject(USupremacySaveGame::StaticClass())))
	{
		SaveGameInstance->Token = "";
		if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveGame", 0))
			UE_LOG(LogAuth, Warning, TEXT("Failed to clear token."));
	}
}

bool UAuthSubsystem::HasInvalidAPIEndpoint() const
{
	if (!APIEndpoint.IsEmpty())
		return false;

	UE_LOG(LogAuth, Warning, TEXT("Auth Subsystem API Endpoint is unset."));
	bool _ = LoginRequestError.ExecuteIfBound("Endpoint unset.");
	return true;
}
