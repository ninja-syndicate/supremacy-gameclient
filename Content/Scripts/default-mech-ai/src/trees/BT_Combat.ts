import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { IsSet } from "../decorators/IsSet"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_SearchTarget } from "./BT_SearchTarget"

export const BT_Combat = new Selector({
    nodes: [
        IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.Both),
        IsSet(BT_SearchTarget, "canSeeTarget", false, ObserverAborts.Self),
    ],
})
