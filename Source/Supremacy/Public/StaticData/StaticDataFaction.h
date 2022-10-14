#pragma once

#include "StaticDataBaseRecord.h"
#include "StaticDataFaction.generated.h"

namespace StaticDataImporter
{
	class Faction;
}

UCLASS(BlueprintType)
class UStaticDataFaction : public UStaticDataBaseRecord
{
public:
	friend class StaticDataImporter::Faction;
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess))
	FString Description;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FColor PrimaryColor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FColor SecondaryColor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FColor BackgroundColor;

	//These aren't URL's because blueprint doesn't support URL's yet...
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString LogoURL;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString BackgroundURL;
};