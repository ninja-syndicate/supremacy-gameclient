import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { BTT_SpecialAttack } from "../tasks/BTT_SpecialAttack"
import { BT_CloseCombat } from "./BT_CloseCombat"
import { BT_RangeCombat } from "./BT_RangeCombat"
import { Predicate } from "../decorators/Predicate"
import { distanceToVec } from "../helper"

export const BT_CanSeeTarget = new Selector({
    nodes: [
        Predicate(
            BTT_SpecialAttack("targetLastKnownLocation"),
            (blackboard: AIBlackboard) => blackboard.canUseSpecialAttack && blackboard.targetLastKnownLocation !== undefined,
            ObserverAborts.LowerPriority,
        ),
        Predicate(
            BT_CloseCombat,
            (blackboard: AIBlackboard) => distanceToVec(blackboard.input.self.location, blackboard.targetLastKnownLocation) <= 5000,
            ObserverAborts.LowerPriority,
        ),
        BT_RangeCombat,
    ],
})
