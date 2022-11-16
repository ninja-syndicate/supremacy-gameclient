#include "Core/Game/SupremacyTypes.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

#include "Core/Game/SupremacyGameInstance.h"

TSubclassOf<UDamageType> USupremacyFunctionLibrary::ConvertToDamageType(const UObject* WorldContextObject, uint8 DamageType)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	const USupremacyGameInstance* SupremacyGameInstance = Cast<USupremacyGameInstance>(GameInstance);
	if (!SupremacyGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("USupremacyFunctionLibrary: Game instance must be USupremacyGameInstance!"));
		return nullptr;
	}

	const TArray<TSubclassOf<UDamageType>>& DamageTypes = SupremacyGameInstance->GetDamageTypes();
	if (DamageType >= DamageTypes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("USupremacyFunctionLibrary: Invalid Damage Type!"));
		return nullptr;
	}
	return DamageTypes[DamageType];
}
