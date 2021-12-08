// Copyright Pandores Marketplace 2021. All Rights Reserved.

#include "BlueprintWebSocketNodes.h"
#include "BlueprintWebSocketWrapper.h"
#include "BlueprintWebSocket.h"

void UWebSocketConnectAsyncProxyBase::Activate()
{
	if (!Socket)
	{
		UE_LOG(LogBlueprintWebSocket, Warning, TEXT("Passed an invalid socket to \"Connect WebSocket\"."));
		OnConnectionError.Broadcast(nullptr, -1, TEXT("Invalid socket"));
		SetReadyToDestroy();
		return;
	}

	if (Socket->IsConnected())
	{
		UE_LOG(LogBlueprintWebSocket, Warning, TEXT("Connect() failed: The socket is already connected."));
		OnConnectionError.Broadcast(nullptr, -1, TEXT("Socket already connected"));
		SetReadyToDestroy();
		return;
	}

	Socket->OnConnectedEvent		.AddDynamic(this, &UWebSocketConnectAsyncProxy::OnConnectedInternal);
	Socket->OnConnectionErrorEvent	.AddDynamic(this, &UWebSocketConnectAsyncProxy::OnConnectionErrorInternal);
	Socket->OnCloseEvent			.AddDynamic(this, &UWebSocketConnectAsyncProxy::OnCloseInternal);
	Socket->OnMessageEvent			.AddDynamic(this, &UWebSocketConnectAsyncProxy::OnMessageInternal);

	Socket->Connect(Url, Protocol);
}

void UWebSocketConnectAsyncProxyBase::InitSocket(UBlueprintWebSocket* const InSocket, const FString& InUrl, const FString InProtocol)
{
	Socket   = InSocket;
	Url		 = InUrl;
	Protocol = InProtocol;
}

void UWebSocketConnectAsyncProxyBase::OnConnectedInternal()
{
	OnConnected.Broadcast(Socket, -1, TEXT("Connected"));
}

void UWebSocketConnectAsyncProxyBase::OnConnectionErrorInternal(const FString& Error)
{
	OnConnectionError.Broadcast(Socket, -1, Error);

	SetReadyToDestroy();
}

void UWebSocketConnectAsyncProxyBase::OnCloseInternal(const int64 Status, const FString& Reason, const bool bWasClean)
{
	OnClose.Broadcast(Socket, Status, Reason);
	SetReadyToDestroy();
}

void UWebSocketConnectAsyncProxyBase::OnMessageInternal(const FString& Message)
{
	OnMessage.Broadcast(Socket, -1, Message);
}


/* static */ UWebSocketConnectAsyncProxy* UWebSocketConnectAsyncProxy::Connect(UBlueprintWebSocket* const WebSocket, const FString& Url, const FString& Protocol)
{
	UWebSocketConnectAsyncProxy* const Proxy = NewObject<UWebSocketConnectAsyncProxy>();

	Proxy->InitSocket(WebSocket, Url, Protocol);

	return Proxy;
}

/* static */ UWebSocketCreateConnectAsyncProxy* UWebSocketCreateConnectAsyncProxy::Connect(const FString& Url, const FString& Protocol, const TMap<FString, FString>& Headers)
{
	ThisClass* const Proxy = NewObject<ThisClass>();

	UBlueprintWebSocket* const Socket = UBlueprintWebSocket::CreateWebSocket();

	Proxy->InitSocket(Socket, Url, Protocol);

	Socket->SetHeaders(Headers);

	return Proxy;
}

UWebSocketReconnectProxy* UWebSocketReconnectProxy::Reconnect(UBlueprintWebSocket* const WebSocket, FString Protocol, FString URL, int32 MaxAttemptCount)
{
	UWebSocketReconnectProxy* const Proxy = NewObject<UWebSocketReconnectProxy>();

	Proxy->WebSocket = WebSocket;
	Proxy->URL = MoveTemp(URL);
	Proxy->RemainingAttempts = MaxAttemptCount;
	Proxy->Protocol = MoveTemp(Protocol);

	return Proxy;
}

void UWebSocketReconnectProxy::Activate()
{
	if (!WebSocket)
	{
		FFrame::KismetExecutionMessage(TEXT("Passed nullptr to Reconnect()."), ELogVerbosity::Error);
		OnFailed();
		return;
	}

	WebSocket->OnConnectionErrorEvent.AddDynamic(this, &ThisClass::OnError);
	WebSocket->OnConnectedEvent      .AddDynamic(this, &ThisClass::OnConnected);

	AttemptConnection();
}

void UWebSocketReconnectProxy::AttemptConnection()
{
	if (WebSocket->IsConnected())
	{
		OnConnected();
		return;
	}

	WebSocket->Connect(URL, Protocol);
}

void UWebSocketReconnectProxy::OnConnected()
{
	UE_LOG(LogBlueprintWebSocket, Log, TEXT("Reconnected to WebSocket server."));

	Connected.Broadcast(WebSocket, FMath::Max(RemainingAttempts, 0));
	SetReadyToDestroy();
}

void UWebSocketReconnectProxy::OnFailed()
{
	UE_LOG(LogBlueprintWebSocket, Error, TEXT("Failed to reconnect to WebSocket server. All attempts exhausted."));

	Failed.Broadcast(WebSocket, 0);
	SetReadyToDestroy();
}

void UWebSocketReconnectProxy::OnError(const FString& ConnectionError)
{
	// We never fail if attempts < 0 (wait until success).
	if (--RemainingAttempts == 0)
	{
		OnFailed();
		return;
	}

	UE_LOG(LogBlueprintWebSocket, Warning, TEXT("Reconnection attempt failed."));

	AttemptFailed.Broadcast(WebSocket, RemainingAttempts);

	AttemptConnection();
}
