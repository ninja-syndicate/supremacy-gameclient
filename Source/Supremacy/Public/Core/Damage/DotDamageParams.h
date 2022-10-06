#pragma once

#include "CoreMinimal.h"
#include "DotDamageParams.generated.h"

USTRUCT(BlueprintType)
struct FDotDamageParams {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dot Damage Parameters")
	float TickDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dot Damage Parameters")
	float TickDuration = 1.0f;

	/** If greater than 0, radial damage will be applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dot Damage Parameters")
	float DamageRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dot Damage Parameters")
	bool bEnableFriendlyFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dot Damage Parameters")
	int	MaxTicks = 0;
};
