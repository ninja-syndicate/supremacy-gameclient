#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamMemberInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeamMemberInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUPREMACY_API ITeamMemberInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	UFUNCTION(Category = "Team Member", BlueprintCallable, BlueprintNativeEvent)
	FString GetTeamID();
};
