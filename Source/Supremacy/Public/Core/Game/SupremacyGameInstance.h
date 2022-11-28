// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SupremacyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API USupremacyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USupremacyGameInstance();

public:
	virtual void Init() override;

public:
	class UStaticData* GetStaticData() const;
	const TArray<TSubclassOf<class UDamageType>>& GetDamageTypes() const;
	const TArray<TEnumAsByte<EPhysicalSurface>>& GetNonflammableSurfaceTypes() const;

protected:
	UPROPERTY(Category = "Supremacy Game Instance", EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UDamageType>> DamageTypes;

	UPROPERTY(Category = "Supremacy Game Instance", EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EPhysicalSurface>> NonflammableSurfaceTypes;

protected:
	/** This can be set from blueprint or from path. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StaticData")
	TObjectPtr<class UStaticData> StaticData = nullptr;
};
