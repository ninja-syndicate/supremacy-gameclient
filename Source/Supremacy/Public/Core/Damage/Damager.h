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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> Instigator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AController> Controller;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Initialize();
	virtual void Initialize_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, BlueprintNativeEvent)
	float ApplyDamage(AActor* DamagedActor, float BaseDamage, TSubclassOf<UDamageType> DamageTypeClass);
	virtual float ApplyDamage_Implementation(AActor* DamagedActor, float BaseDamage, TSubclassOf<UDamageType> DamageTypeClass);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
