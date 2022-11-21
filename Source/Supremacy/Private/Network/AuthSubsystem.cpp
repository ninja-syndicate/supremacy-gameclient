#include "Network/AuthSubsystem.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"

DEFINE_LOG_CATEGORY(LogAuth);

void UAuthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Http = &FHttpModule::Get();

	if (APIEndpoint.IsEmpty())
	{
		UE_LOG(LogAuth, Warning, TEXT("Auth Subsystem API Endpoint is unset."))
	}
}

void UAuthSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAuthSubsystem::Login(const FString& Email, const FString& Password) const
{
	// const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	//
	// Request->OnProcessRequestComplete().BindUObject(this, &UAuthSubsystem::OnLoginRequestComplete);
	// Request->SetURL(APIEndpoint + "/api/email");
	// Request->SetVerb("POST");
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	//
	// FString JsonString;
	// FLoginRequest Payload;
	// Payload.Email = Email;
	// Payload.Password = Password;
	// FJsonObjectConverter::UStructToJsonObjectString(Payload, JsonString);
	// Request->SetContentAsString(JsonString);
	//
	// Request->ProcessRequest();
}

void UAuthSubsystem::OnLoginRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogAuth, Warning, TEXT("Login Request Failed"))
		return;
	}

	UE_LOG(LogAuth, Warning, TEXT("%s"), *Response->GetContentAsString())
	//LoginRequestComplete.Broadcast();
}
