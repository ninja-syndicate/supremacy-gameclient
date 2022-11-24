// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWebBrowser.h"
#include "SWebBrowser.h"

void UCustomWebBrowser::BindUObject(const FString& Name, UObject* Object, bool bIsPermanent)
{
	if (WebBrowserWidget.IsValid())
	{
		WebBrowserWidget->BindUObject(Name, Object, bIsPermanent);
	}
}