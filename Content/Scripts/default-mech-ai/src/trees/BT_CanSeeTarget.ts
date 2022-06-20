import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { BTT_SpecialAttack } from "../tasks/BTT_SpecialAttack"
import { BT_CloseCombat } from "./BT_CloseCombat"
import { BT_RangeCombat } from "./BT_RangeCombat"
import { Predicate } from "../decorators/Predicate"
import { distanceToVec } from "../helper"

export const BT_CanSeeTarget = new Selector({
    nodes: [
        /*
        Predicate(
            BTT_SpecialAttack("targetLastKnownLocation"),
            (blackboard: AIBlackboard) => blackboard.canUseSpecialAttack && blackboard.targetLastKnownLocation !== undefined,
            true,
            ObserverAborts.LowerPriority,
        ),
        */
        /*
        Predicate(
            BT_CloseCombat,
            (blackboard: AIBlackboard) =>
                blackboard.canMelee &&
                blackboard.targetLastKnownLocation !== undefined &&
                distanceToVec(blackboard.input.self.location, blackboard.targetLastKnownLocation) <= 4000,
            true,
            ObserverAborts.Both,
        ),
        */
        BT_RangeCombat,
    ],
})
