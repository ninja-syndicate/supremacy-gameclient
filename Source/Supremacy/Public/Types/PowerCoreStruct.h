#pragma once

#include "CoreMinimal.h"
#include "PowerCoreStruct.generated.h"

USTRUCT(BlueprintType)
struct FPowerCoreStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="power_capacity"))
	float PowerCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="recharge_rate"))
	float RechargeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="max_draw_rate"))
	float MaxDrawRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="weapon_system_allocation"))
	float WeaponSystemAllocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="movement_system_allocation"))
	float MovementSystemAllocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="utility_system_allocation"))
	float UtilitySystemAllocation;

	FPowerCoreStruct(): PowerCapacity(0), RechargeRate(0), MaxDrawRate(0), WeaponSystemAllocation(0),
	                    MovementSystemAllocation(0),
	                    UtilitySystemAllocation(0)
	{}
};
