#pragma once

#include "Interactable.h"
#include "PickUp.generated.h"

UINTERFACE(Blueprintable)
class UPickUp : public UInteractable
{
    GENERATED_BODY()
};

/**
 *
 */
class SUPREMACY_API IPickUp : public IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};