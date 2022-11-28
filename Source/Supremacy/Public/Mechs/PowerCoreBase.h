#pragma once

#include "CoreMinimal.h"
#include "PowerCoreBase.generated.h"

UCLASS(Blueprintable)
class SUPREMACY_API UPowerCoreBase : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetWeaponSystemCurrentPower();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetShieldSystemCurrentPower();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		float GetMovementSystemCurrentPower();
};
