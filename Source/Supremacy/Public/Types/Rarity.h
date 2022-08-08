#pragma once

#include "CoreMinimal.h"
#include "Rarity.generated.h"

UENUM()
enum ERarity
{
	Rarity_Default UMETA(DisplayName = "Default"),
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
