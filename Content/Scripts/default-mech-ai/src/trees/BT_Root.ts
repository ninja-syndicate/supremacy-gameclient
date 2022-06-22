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
import { HasLowShield } from "../predicates/Predicate_HasLowShield"
import { BT_LookAround } from "./BT_LookAround"
import { BTT_Wait } from "../tasks/BTT_Wait"
import { BT_GetPickup } from "./BT_GetPickup"
import { BT_Test } from "./BT_Test"
import { BTT_Taunt } from "../tasks/BTT_Taunt"
import { Action } from "enums"
import { CanActivateAction } from "../decorators/CanActivateAction"

/**
 *
 */
export const BT_Root = new Selector({
    nodes: [
        IsSet(BT_Combat, "target", true, ObserverAborts.Both),
        IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, HasLowShield, true, ObserverAborts.LowerPriority),
        CanActivateAction(BTT_Taunt, Action.Taunt, true),
        IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BT_InvestigateNoise, "heardNoise", true, ObserverAborts.LowerPriority),
        BT_Patrol,
        BTT_Wait(1),
    ],
})
