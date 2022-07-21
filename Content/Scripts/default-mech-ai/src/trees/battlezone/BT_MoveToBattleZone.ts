import { ObserverAborts, Sequence } from "behaviortree"
import { EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { Predicate_IsLocationInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { Predicate } from "@decorators/Predicate"

/**
 * Moving to the main battle zone behavior.
 *
 * Makes an environment query to get a location inside the battle zone and moves to it (@see {@link EQSQueryType.BattleZone}). If the current move to the battle
 * zone location is no longer actually inside the battle zone (as a result of shrinkage/movement), the move to will be aborted.
 *
 * Note that {@link EQSQueryType.BattleZone} will still generate a location even when the battle zone disappears.
 */
export const BT_MoveToBattleZone = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.BattleZone, "battleZoneLocation"),
        Predicate(BTT_MoveTo("battleZoneLocation"), Predicate_IsLocationInsideBattleZone("battleZoneLocation"), true, ObserverAborts.Self),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.battleZoneLocation = undefined)),
    ],
})
