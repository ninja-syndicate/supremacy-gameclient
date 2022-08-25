#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

USTRUCT(BlueprintType)
struct FTheme {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="primary"))
	FString Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="secondary"))
	FString Secondary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="background"))
	FString Background;
};

USTRUCT(BlueprintType)
struct FFactionServer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="id"))
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="label"))
	FString Label;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="image_url"))
	FString ImageURL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="theme"))
	FTheme Theme;
};

USTRUCT(BlueprintType)
struct FFaction {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="id"))
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="name"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="color"))
	FColor Color;

	explicit FFaction(const FFactionServer& FactionServer) : ID(FactionServer.ID), Name(FactionServer.Label), Color(FColor::FromHex(FactionServer.Theme.Primary))
	{}
	
	FFaction(): Color(FColor(255, 255, 255, 255)) {}
};
