#pragma once

#include "GameFramework/GameUserSettings.h"
#include "SupremacyUserSettings.generated.h"

UCLASS(config=GameUserSettings)
class SUPREMACY_API USupremacyUserSettings final : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static USupremacyUserSettings* GetUserSettings();

	/** Sets the user setting for HUD Enabled. See UGameUserSettings::bHUDEnabled. */
	UFUNCTION(BlueprintCallable, Category=Settings)
	void SetHUDEnabled(const bool bEnable);

	/** Returns the user setting for HUD Enabled. */
	UFUNCTION(BlueprintPure, Category=Settings)
	bool IsHUDEnabled() const;

	/** Whether the HUD is enabled by default or not. (public to allow UI to connect to it) */
	UPROPERTY(Config)
	bool bHUDEnabled;
 };