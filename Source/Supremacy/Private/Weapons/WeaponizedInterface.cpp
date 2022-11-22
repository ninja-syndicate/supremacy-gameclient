// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponizedInterface.h"

// Add default functionality here for any IWeaponizedInterface functions that are not pure virtual.
float IWeaponizedInterface::GetWeaponBaseScale_Implementation()
{
	// Use the base scale of 1 by default.
	return 1.0f;
}