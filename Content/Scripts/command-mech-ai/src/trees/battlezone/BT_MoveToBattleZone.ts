import { ObserverAborts, Sequence } from "behaviortree"
import { EQSQueryType, MovementMode } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { Predicate_IsLocationInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { Predicate } from "@decorators/Predicate"
import { BT_SprintMoveTo } from "@trees/movement/BT_MovementMode"

/**
 * Move to battle zone behavior.
 *
 * Makes an environment query to get a location inside the battle zone and moves to it (@see {@link EQSQueryType.BattleZone}). Also, it will set the current
 * movement mode to {@link MovementMode.Sprint}. If the current move to the battle zone location is no longer actually inside the battle zone (as a result of
 * shrinkage/movement), the current move to will be aborted.
 *
 * Note that {@link EQSQueryType.BattleZone} will still generate a location even when the battle zone disappears. This location will be near the disappeared
 * battle zone location.
 */
export const BT_MoveToBattleZone = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.BattleZone, "battleZoneLocation"),
        // TODO: Add a loop to re-try rather than aborting immediately.
        Predicate(BT_SprintMoveTo("battleZoneLocation"), Predicate_IsLocationInsideBattleZone("battleZoneLocation"), true, ObserverAborts.Self),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.battleZoneLocation = undefined)),
    ],
})
