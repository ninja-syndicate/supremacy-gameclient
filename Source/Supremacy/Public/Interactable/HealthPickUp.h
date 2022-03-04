#pragma once

#include "PickUp.h"
#include "HealthPickUp.generated.h"

UINTERFACE()
class UHealthPickUp : public UPickUp
{
    GENERATED_BODY()
};

/**
 *
 */
class SUPREMACY_API IHealthPickUp : public IPickUp
{
	GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};