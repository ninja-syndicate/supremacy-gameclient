#pragma once

#include "CrowdAIController.h"
#include "ScriptedAIController.generated.h"

UCLASS()
class AScriptedAIController : public ACrowdAIController
{
	GENERATED_BODY()
	
public:
	AScriptedAIController();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BrainTick();

	UPROPERTY(VisibleAnywhere)
	class UJavascriptInstanceComponent* JavascriptInstance;
};
