#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "Utility.generated.h"

UCLASS()
class SUPREMACY_API AUtility final : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUtility();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags", Replicated)
    FGameplayTagContainer GameplayTagContainer;

public:	
	
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer; }
};
