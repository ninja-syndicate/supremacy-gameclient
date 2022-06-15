import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { IsSet } from "../decorators/IsSet"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_SearchTarget } from "./BT_SearchTarget"
import { Predicate } from "../decorators/Predicate"
import { AIBlackboard } from "../blackboard"
import { BT_Camp } from "./BT_Camp"

export const BT_Combat = new Selector({
    nodes: [
        IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        Predicate(BT_Camp, (blackboard: AIBlackboard) => {
            let self = blackboard.input.self
            return self.shield / self.shieldMax <= 0.4
        }),
        Predicate(
            BT_ReceivedDamage,
            (blackboard: AIBlackboard) => !blackboard.canSeeTarget && blackboard.damageStimulusFocalPoint !== undefined,
            true,
            ObserverAborts.LowerPriority,
        ),
        Predicate(BT_SearchTarget, (blackboard: AIBlackboard) => !blackboard.canSeeTarget),
    ],
})
