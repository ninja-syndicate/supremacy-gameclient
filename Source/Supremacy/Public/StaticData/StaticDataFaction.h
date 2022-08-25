#pragma once

#include "StaticDataBaseRecord.h"
#include "StaticDataFaction.generated.h"

USTRUCT(BlueprintType)
struct FStaticDataFaction : public FStaticDataBaseRecord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FString Description;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FColor PrimaryColor;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FColor SecondaryColor;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FColor BackgroundColor;

	//These aren't URL's because blueprint doesn't support URL's yet...
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FString LogoURL;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FString BackgroundURL;
};