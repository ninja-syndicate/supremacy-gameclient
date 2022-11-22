#include "Network/AuthSubsystem.h"
#include "JsonObjectConverter.h"

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

void UAuthSubsystem::GetUser(bool& Valid, FUser& User) const
{
	if (CurrentToken.IsEmpty())
		return;

	Valid = true;
	User = CurrentUser;
}

void UAuthSubsystem::GetToken(bool& Valid, FString& Token) const
{
	if (CurrentToken.IsEmpty())
		return;

	Valid = true;
	Token = CurrentToken;
}

void UAuthSubsystem::LoginEmail(const FString& Email, const FString& Password, const FLoginRequestComplete OnComplete, const FLoginRequestError OnError)
{
	LoginRequestComplete = OnComplete;
	LoginRequestError = OnError;
	
	if (APIEndpoint.IsEmpty())
	{
		UE_LOG(LogAuth, Warning, TEXT("Auth Subsystem API Endpoint is unset."));
		bool _ = LoginRequestError.ExecuteIfBound("Endpoint unset.");
		return;
	}
	
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

void UAuthSubsystem::LoginToken(const FString& Token, const FLoginRequestComplete OnComplete, const FLoginRequestError OnError)
{
	LoginRequestComplete = OnComplete;
	LoginRequestError = OnError;

	if (APIEndpoint.IsEmpty())
	{
		UE_LOG(LogAuth, Warning, TEXT("Auth Subsystem API Endpoint is unset."));
		bool _ = LoginRequestError.ExecuteIfBound("Endpoint unset.");
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

void UAuthSubsystem::OnLoginRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool Success) const
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
		{
			UE_LOG(LogAuth, Warning, TEXT("Login error and delegate was unbound."));
		}
		return;
	}
	
	if (Request->GetURL().EndsWith("token"))
	{
		FLoginTokenResponse Payload;
		FJsonObjectConverter::JsonObjectStringToUStruct(*Response->GetContentAsString(), &Payload);
		if (!LoginRequestComplete.ExecuteIfBound(Payload.User, Payload.Token))
		{
			UE_LOG(LogAuth, Warning, TEXT("Login succeced but no delegate was bound."));
		}
	}
	else
	{
		FLoginEmailResponse Payload;
		FJsonObjectConverter::JsonObjectStringToUStruct(*Response->GetContentAsString(), &Payload);
		if (!LoginRequestComplete.ExecuteIfBound(Payload.User, Payload.Issue_Token))
		{
			UE_LOG(LogAuth, Warning, TEXT("Login succeced but no delegate was bound."));
		}
	}
}
