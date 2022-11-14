#include "GameFramework/SupremacyUserSettings.h"

USupremacyUserSettings* USupremacyUserSettings::GetUserSettings()
{
	return Cast<USupremacyUserSettings>(GetGameUserSettings());
}

void USupremacyUserSettings::SetHUDEnabled(const bool bEnable)
{
	bHUDEnabled = bEnable;
}

bool USupremacyUserSettings::IsHUDEnabled() const
{
	return bHUDEnabled;
}
