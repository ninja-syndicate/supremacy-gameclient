// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebBrowser.h"
#include "CustomWebBrowser.generated.h"

/**
 * 
 */
UCLASS()
class SUPREMACY_API UCustomWebBrowser : public UWebBrowser
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent);

};
