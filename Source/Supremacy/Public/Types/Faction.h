#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

USTRUCT(BlueprintType)
struct FTheme {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Secondary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Background;
};

USTRUCT(BlueprintType)
struct FFactionServer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Label;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Image_URL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTheme Theme;
};

USTRUCT(BlueprintType)
struct FFaction {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;

	explicit FFaction(const FFactionServer& FactionServer) : ID(FactionServer.ID), Name(FactionServer.Label), Color(FColor::FromHex(FactionServer.Theme.Primary))
	{}
	
	FFaction(): Color(FColor(255, 255, 255, 255)) {}
};
