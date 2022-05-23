#include "AI/ScriptedAIController.h"

#include "../../../../Plugins/UnrealJs/Source/V8/Public/JavascriptInstanceComponent.h"

AScriptedAIController::AScriptedAIController()
{
	JavascriptInstance = CreateDefaultSubobject<UJavascriptInstanceComponent>(TEXT("JavascriptInstance"));
}

void AScriptedAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScriptedAIController::BrainTick()
{
}
