// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damager.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPREMACY_API UDamager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamager();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Initialize();
	virtual void Initialize_Implementation();

	UFUNCTION(Category = "Damager", BlueprintCallable, BlueprintAuthorityOnly, BlueprintNativeEvent)
	float ApplyDamage(AActor* DamagedActor, float BaseDamage, TSubclassOf<UDamageType> DamageTypeClass);
	virtual float ApplyDamage_Implementation(AActor* DamagedActor, float BaseDamage, TSubclassOf<UDamageType> DamageTypeClass);

	UFUNCTION(Category = "Damager", BlueprintCallable, BlueprintNativeEvent)
	void SetDamageByWeaponStruct(const struct FWeaponStruct& WeaponStruct);
	virtual void SetDamageByWeaponStruct_Implementation(const struct FWeaponStruct& WeaponStruct);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	/** The amount of damage this damager will apply. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double Damage = 10.0;

	/** The distance at which the damage starts to decrease. If zero, no falloff. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double DamageFalloff = 0.0;

	/** How much the damage decreases by per km. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double DamageFalloffRate = 0.0;

	/** The damage radius. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double DamageRadius = 0.0;

	/** Same as `DamageFalloff`, but must be between 0 and RadialDamageRadius to have any effects. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double DamageRadiusFalloff = 0.0;

	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDamageType> DamageType = nullptr;

protected:
	/** The minimum radius the Force Field that deals damage to destructibles will be. */
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	double DestructionMinRadius = 2.0;

protected:
	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> Instigator;

	UPROPERTY(Category = "Damager", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AController> Controller;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
