#pragma once

#include "CoreMinimal.h"
#include "AbilityID.generated.h"

UENUM(BlueprintType)
enum class EAbilityID : uint8
{
	AbilityID_Airstrike UMETA(DisplayName = "Airstrike"),
	AbilityID_Nuke UMETA(DisplayName = "Nuke"),
	AbilityID_Heal UMETA(DisplayName = "Heal"),
	AbilityID_RobotDogs UMETA(DisplayName = "Robot Dogs"),
	AbilityID_RedMountainReinforcement UMETA(DisplayName = "Red Mountain Reinforcement"),
	AbilityID_SatelliteOverload UMETA(DisplayName = "Satellite Overload"),
	AbilityID_LowerTile UMETA(DisplayName = "Lower Tile"),
	AbilityID_Fireworks UMETA(DisplayName = "Fireworks"),
	AbilityID_MoveCommand UMETA(DisplayName = "Move Command", ToolTip="Moving the mech to the desired location."),
	AbilityID_CancelMoveCommand UMETA(DisplayName = "Cancel Move Command", ToolTip="Cancels the requested move command."),
	AbilityID_ShieldBuff UMETA(DisplayName = "Shield Buff"),
	AbilityID_Landmines UMETA(DisplayName = "Landmines"),
	AbilityID_EMP UMETA(DisplayName = "EMP"),
	AbilityID_HackerDrone UMETA(DisplayName = "Hacker Drone"),
	AbilityID_CameraDrone UMETA(DisplayName = "Camera Drone"),
	AbilityID_Incognito UMETA(DisplayName = "Incognito"),
	AbilityID_Blackout UMETA(DisplayName = "Blackout"),
	AbilityID_Ammo UMETA(DisplayName = "Ammo"),
	AbilityID_MiniMech UMETA(DisplayName = "Mini Mech", ToolTip="Spawns the mini genesis mech for the faction to the specified location."),
	AbilityID_Turret UMETA(DisplayName = "Turret"),
	AbilityID_K9PatrolPack UMETA(DisplayName = "K9 Patrol Pack", ToolTip="Spawns a pack of robot dogs that guards the given location.")
};
