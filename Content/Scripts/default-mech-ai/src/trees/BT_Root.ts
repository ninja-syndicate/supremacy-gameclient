import { ObserverAborts, Selector } from "behaviortree"
import { BT_Combat } from "./BT_Combat"
import { BT_Patrol } from "./BT_Patrol"
import { BT_InvestigateNoise } from "./BT_InvestigateNoise"
import { IsSet } from "../decorators/IsSet"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"

export const BT_Root = new Selector({
    nodes: [
        IsSet(BT_Combat, "target", true, ObserverAborts.Both),
        IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BT_InvestigateNoise, "heardNoise", true, ObserverAborts.LowerPriority),
        IsSet(BT_Patrol, "target", false),
    ],
})
