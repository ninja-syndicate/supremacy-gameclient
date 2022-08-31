#pragma once

#include "CoreMinimal.h"
#include "Rarity.generated.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Rarity_Default = 0 UMETA(DisplayName = "Default"),
	Rarity_Mega UMETA(DisplayName = "Mega"),
	Rarity_Colossal UMETA(DisplayName = "Colossal"),
	Rarity_Rare UMETA(DisplayName = "Rare"),
	Rarity_Legendary UMETA(DisplayName = "Legendary"),
	Rarity_EliteLegendary UMETA(DisplayName = "Elite Legendary"),
	Rarity_UltraRare UMETA(DisplayName = "Ultra Rare"),
	Rarity_Exotic UMETA(DisplayName = "Exotic"),
	Rarity_Guardian UMETA(DisplayName = "Guardian"),
	Rarity_Mythic UMETA(DisplayName = "Mythic"),
	Rarity_DeusEx UMETA(DisplayName = "Deus Ex"),
	Rarity_Titan UMETA(DisplayName = "Titan"),
};

const TMap<FString, ERarity> StringToERarity = {
	{ "MEGA", ERarity::Rarity_Mega },
	{ "COLOSSAL", ERarity::Rarity_Colossal },
	{ "RARE", ERarity::Rarity_Rare },
	{ "LEGENDARY", ERarity::Rarity_Legendary },
	{ "ELITE_LEGENDARY", ERarity::Rarity_EliteLegendary },
	{ "ULTRA_RARE", ERarity::Rarity_UltraRare },
	{ "EXOTIC", ERarity::Rarity_Exotic },
	{ "GUARDIAN", ERarity::Rarity_Guardian },
	{ "MYTHIC", ERarity::Rarity_Mythic },
	{ "DEUS_EX", ERarity::Rarity_DeusEx },
	{ "TITAN", ERarity::Rarity_Titan },
};
