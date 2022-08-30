#pragma once

#include "CoreMinimal.h"
#include "DamageHistory.generated.h"

USTRUCT(BlueprintType)
struct FDamageHistoryResultItem {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Instigator_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Source_Hash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Source_Name;

	FDamageHistoryResultItem(): Amount(0) {}
};

USTRUCT(BlueprintType)
struct FDamageHistoryItem : public FDamageHistoryResultItem {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Shield_Damage;

	FDamageHistoryItem() : Shield_Damage(false) {}
};
