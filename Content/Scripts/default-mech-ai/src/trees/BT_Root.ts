import { ObserverAborts, Selector } from "behaviortree"
import { BT_Combat } from "./BT_Combat"
import { BT_Patrol } from "./BT_Patrol"
import { BT_InvestigateNoise } from "./BT_InvestigateNoise"
import { IsSet } from "../decorators/IsSet"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"
import { BT_GetCover } from "./BT_GetCover"
import { Predicate } from "../decorators/Predicate"
import { AIBlackboard } from "../blackboard"
import { BT_Camp } from "./BT_Camp"

const shouldRetreat = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= 0.3
}

/**
 *
 */
export const BT_Root = new Selector({
    nodes: [
        IsSet(BT_Combat, "target", true, ObserverAborts.Both),
        Predicate(BT_Camp, shouldRetreat),
        IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BT_InvestigateNoise, "heardNoise", true, ObserverAborts.LowerPriority),
        BT_Patrol,
    ],
})
