#pragma once

#include "CoreMinimal.h"
#include "PowerCoreStruct.generated.h"

USTRUCT(BlueprintType)
struct FPowerCoreStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power_Capacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Recharge_Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max_Draw_Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weapon_System_Allocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Movement_System_Allocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Utility_System_Allocation;

	FPowerCoreStruct(): Power_Capacity(0), Recharge_Rate(0), Max_Draw_Rate(0), Weapon_System_Allocation(0),
	                    Movement_System_Allocation(0),
	                    Utility_System_Allocation(0)
	{}
};
