import { ObserverAborts, Selector } from "behaviortree"
import { Action } from "enums"
import { CanActivateAction } from "../decorators/CanActivateAction"
import { IsSet } from "../decorators/IsSet"
import { Predicate } from "../decorators/Predicate"
import { HasLowShield } from "../predicates/Predicate_HasLowShield"
import { BTT_Taunt } from "../tasks/BTT_Taunt"
import { BTT_Wait } from "../tasks/BTT_Wait"
import { BT_Camp } from "./BT_Camp"
import { BT_Combat } from "./combat/BT_Combat"
import { BT_GetPickup } from "./BT_GetPickup"
import { BT_InvestigateNoise } from "./BT_InvestigateNoise"
import { BT_Patrol } from "./BT_Patrol"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"

/**
 * The root of the behavior tree for AI.
 *
 * Perform a selection of behavior trees/tasks listed under nodes property based on the specified conditions.
 * The higher priority behaviors are placed on top, and specifying aborting conditions via {@link ObserverAborts}.
 *
 * Currently, the behavior of AI is broken into following sub-behaviors:
 *
 * - {@link BT_Combat} -
 * - {@link BT_GetPickup} -
 * - {@link BT_Camp} -
 * - {@link BTT_Taunt} -
 * - {@link BT_ReceivedDamage} -
 * - {@link BT_InvestigateNoise} -
 * - {@link BT_Patrol} -
 *
 * The {@link BTT_Wait} is a fallback task when every other behaviors fail. This may be because your AI temporaily lost control via user actions, stuck or error
 * in your logic.
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
