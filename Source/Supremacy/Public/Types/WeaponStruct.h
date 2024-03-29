#pragma once

#include "CoreMinimal.h"
#include "WeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="UUID that client uses to apply weapon stats to the correct weapons (unique per model/blueprint.)"))
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Unique hash of a user's weapon."))
	FString Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Model_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Skin_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Socket_Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Distance at which damage starts decreasing."))
	int Damage_Falloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="How much the damage decreases by per km."))
	int Damage_Falloff_Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Enemies within this radius when the projectile hits something is damaged."))
	int Damage_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Distance at which damage starts decreasing (must be greater than 0 and less than damageRadius to have any affect.)"))
	int Damage_Radius_Falloff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Damage_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Melee_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees."))
	float Spread;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Rounds per minute"))
	float Rate_Of_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Rounds per minute within the burst of fire (rateOfFire is used for the time between bursts.)"))
	float Burst_Rate_Of_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="cm/s"))
	int Projectile_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="The max amount of ammo this weapon can hold."))
	int Max_Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="The amount of projectile spawned per shot or burst."))
	int Projectile_Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The life span of this weapon's projectile. If non-positive value, projectile's default initial life span will be used."))
	float Projectile_Life_Span = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The damage dealt each tick."))
	float Dot_Tick_Damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The duration of each tick."))
	float Dot_Tick_Duration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "The maximum number of ticks."))
	int Dot_Max_Ticks = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Time before weapon starts firing (eg: minigun spin-up.)"))
	float Charge_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Arcs projectiles towards their target location. Spread becomes radius offset."))
	bool Is_Arced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="For AI reference."))
	int Optimal_Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "For recoil on the Mech's arms."))
	float Recoil_Force;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Idle_Power_Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power_Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Power_Instance_Drain;
	
	FWeaponStruct(): Socket_Index(0),
	                 Damage(0),
	                 Damage_Falloff(0),
	                 Damage_Falloff_Rate(0),
	                 Damage_Radius(0),
	                 Damage_Radius_Falloff(0),
	                 Damage_Type(0),
					 Melee_Damage(20),
	                 Spread(0),
	                 Rate_Of_Fire(0),
	                 Burst_Rate_Of_Fire(0),
	                 Projectile_Speed(0),
	                 Max_Ammo(0),
	                 Projectile_Amount(0),
	                 Charge_Time(0),
	                 Is_Arced(false),
	                 Optimal_Range(0),
	                 Recoil_Force(0),
	                 Idle_Power_Cost(0), Power_Cost(0), Power_Instance_Drain(false)
	{
	}
};
