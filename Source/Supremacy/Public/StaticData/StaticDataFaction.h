#pragma once

#include "StaticDataBaseRecord.h"
#include "StaticDataFactionPalette.h"
#include "Types/Faction.h"
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

	//These aren't URL's because blueprint doesn't support URL's yet...
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString LogoURL;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	FString BackgroundURL;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Fields", meta=(AllowPrivateAccess=true))
	UStaticDataFactionPalette* Palette;

	UFUNCTION(BlueprintPure, meta=(DisplayName="To Faction (From StaticDataFaction)", CompactNodeTitle = "->", BlueprintAutocast))
	FFaction ToFaction() const
	{
		FFaction Struct;
		Struct.ID = ID.ToString(EGuidFormats::DigitsWithHyphens).ToLower();
		Struct.Name = Label;
		if (Palette) Struct.Color = Palette->S400;
		
		return Struct;
	}
};