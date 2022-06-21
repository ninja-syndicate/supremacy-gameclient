import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { IsSet } from "../decorators/IsSet"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_SearchTarget } from "./BT_SearchTarget"
import { Predicate } from "../decorators/Predicate"
import { AIBlackboard } from "../blackboard"
import { BT_Camp } from "./BT_Camp"
import { HasLowShield } from "../predicates/Predicate_HasLowShield"
import { BT_GetPickup } from "./BT_GetPickup"

export const BT_Combat = new Selector({
    nodes: [
        IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, HasLowShield, true, ObserverAborts.LowerPriority),
        Predicate(
            BT_ReceivedDamage,
            (blackboard: AIBlackboard) => !blackboard.canSeeTarget && blackboard.damageStimulusFocalPoint !== undefined && !blackboard.isLastDamageFromTarget,
            true,
            ObserverAborts.LowerPriority,
        ),
        Predicate(BT_SearchTarget, (blackboard: AIBlackboard) => !blackboard.canSeeTarget),
    ],
})
