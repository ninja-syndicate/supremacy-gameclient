import { Predicate } from "@decorators/Predicate"
import { Predicate_IsTargetInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { AIBlackboard } from "@blackboards/blackboard"
import { Predicate_TargetInRange } from "@root/predicates/Predicate_InRange"
import { ObserverAborts, Selector } from "behaviortree"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"
import { BT_CloseStrafe } from "@trees/BT_CloseStrafe"
import { BT_MoveByDistanceToTarget } from "@trees/movement/BT_MovementMode"

export const BT_CloseCombatMovement = new Selector({
    nodes: [
        Predicate(
            Predicate(BT_MoveByDistanceToTarget("targetLastKnownLocation", true), Predicate_IsTargetInsideBattleZone, true, ObserverAborts.Self),
            (blackboard: AIBlackboard) => !Predicate_TargetInRange(CURRENT_AI_CONFIG.closeCombatKeepRange)(blackboard),
            true,
            ObserverAborts.LowerPriority,
        ),
        BT_CloseStrafe,
    ],
})
