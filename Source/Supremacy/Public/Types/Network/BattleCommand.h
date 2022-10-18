#pragma once

#include "CoreMinimal.h"
#include "BattleCommand.generated.h"

UENUM(BlueprintType)
enum EBattleCommand
{
	BattleCommand_Init UMETA(DisplayName = "BATTLE:INIT", ToolTip="Command sent from game server to request a new battle"),
	BattleCommand_Start UMETA(DisplayName = "BATTLE:START", ToolTip="Command sent to the game server after the battle as been setup; telling it about initial positions"),
	BattleCommand_End UMETA(DisplayName = "BATTLE:END", ToolTip="Command sent to the game server when the battle is finished"),
	BattleCommand_War_Machine_Destroyed UMETA(DisplayName = "BATTLE:WAR_MACHINE_DESTROYED", ToolTip="Command sent to the game server to tell it a WarMachine was destroyed"),
	BattleCommand_Ability UMETA(DisplayName = "BATTLE:ABILITY", ToolTip="Command  sent from the game server to activate an ability (eg: airstrike)"),
	BattleCommand_Ready UMETA(DisplayName = "BATTLE:READY", ToolTip="Command sent to the game server to say the client is ready for a new battle"),
	BattleCommand_AI_Spawned UMETA(DisplayName = "BATTLE:AI_SPAWNED", ToolTip="Command sent to the game server to say a new AI was spawned"),
	BattleCommand_Intro_Finished UMETA(DisplayName = "BATTLE:INTRO_FINISHED", ToolTip="Command sent to the game server when the intro animation is complete"),
	BattleCommand_Map_Details UMETA(DisplayName = "BATTLE:MAP_DETAILS", ToolTip="Command sent to the game server after BATTLE:INIT with the details of the map about to be loaded"),
	BattleCommand_War_Machine_Pickup UMETA(DisplayName = "BATTLE:WAR_MACHINE_PICKUP", ToolTip="Command sent to the game server when a mech activates a pickup (eg: heal crate)"),
	BattleCommand_Outro_Finished UMETA(DisplayName = "BATTLE:OUTRO_FINISHED", ToolTip="Command sent to the game server when the outro animation is complete"),
	BattleCommand_Set_Stats UMETA(DisplayName = "BATTLE:SET_STATS", ToolTip="Command sent from the game server to update the default stats for abilities and weapons"),
	BattleCommand_Ability_Move_Command_Complete UMETA(DisplayName = "BATTLE:ABILITY_MOVE_COMMAND_COMPLETE", ToolTip="Command sent to the game server when a war machine has completed it's move command"),
	BattleCommand_Ability_Move_Command_Response UMETA(DisplayName = "BATTLE:ABILITY_MOVE_COMMAND_RESPONSE", ToolTip="Command sent to the game server when a mech command start succeeded/failed"),
	BattleCommand_Zone_Change UMETA(DisplayName = "BATTLE:ZONE_CHANGE", ToolTip="Command sent to the game server when the battle zone is about to change"),
	BattleCommand_Ability_Complete UMETA(DisplayName = "BATTLE:ABILITY_COMPLETE", ToolTip="Command sent to the game server when a ability finishes (to update the minimap)"),
	BattleCommand_War_Machine_Status UMETA(DisplayName = "BATTLE:WAR_MACHINE_STATUS", ToolTip="Command sent to the game server whenever a war machine status has changed."),
};

const TMap<EBattleCommand, FString> BattleCommandToString = {
	{ BattleCommand_Init, "BATTLE:INIT" },
	{ BattleCommand_Start, "BATTLE:START" },
	{ BattleCommand_End, "BATTLE:END" },
	{ BattleCommand_War_Machine_Destroyed, "BATTLE:WAR_MACHINE_DESTROYED" },
	{ BattleCommand_Ability, "BATTLE:ABILITY" },
	{ BattleCommand_Ready, "BATTLE:READY" },
	{ BattleCommand_AI_Spawned, "BATTLE:AI_SPAWNED" },
	{ BattleCommand_Intro_Finished, "BATTLE:INTRO_FINISHED" },
	{ BattleCommand_Map_Details, "BATTLE:MAP_DETAILS" },
	{ BattleCommand_War_Machine_Pickup, "BATTLE:WAR_MACHINE_PICKUP" },
	{ BattleCommand_Outro_Finished, "BATTLE:OUTRO_FINISHED" },
	{ BattleCommand_Set_Stats, "BATTLE:SET_STATS" },
	{ BattleCommand_Ability_Move_Command_Complete, "BATTLE:ABILITY_MOVE_COMMAND_COMPLETE" },
	{ BattleCommand_Ability_Move_Command_Response, "BATTLE:ABILITY_MOVE_COMMAND_RESPONSE" },
	{ BattleCommand_Zone_Change, "BATTLE:ZONE_CHANGE" },
	{ BattleCommand_Ability_Complete, "BATTLE:ABILITY_COMPLETE" },
	{ BattleCommand_War_Machine_Status, "BATTLE:WAR_MACHINE_STATUS" },
};
