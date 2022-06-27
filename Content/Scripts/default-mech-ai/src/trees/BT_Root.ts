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
 * The higher priority behaviors are placed on top, and you can specify aborting conditions via {@link ObserverAborts}.
 *
 * Currently, the root behavior of AI is broken into following sub-behaviors:
 *
 * - {@link BT_Combat} if AI has {@link AIBlackboard.target}
 * - {@link BT_GetPickup} if AI has {@link AIBlackboard.desiredPickupLocation} such as heal crate location
 * - {@link BT_Camp} if AI has low shield (@see {@link HasLowShield})
 * - {@link BTT_Taunt} if AI can taunt (i.e. not on a cooldown)
 * - {@link BT_ReceivedDamage} if AI has the {@link AIBlackboard.damageStimulusFocalPoint} set as a result of receiving a damage
 * - {@link BT_InvestigateNoise} if AI heard a noise ({@link AIBlackboard.HeardNoise}) which may be taunt, gunshot or something else
 * - {@link BT_Patrol} otherwise
 *
 * The wrapping function around these behaviors are decorators (@see {@link IsSet}, {@link Predicate} and {@link CanActivateAction}). They are used to specify
 * the conditions to enter that behavior. And the {@link ObseverAborts} is used to specify aborting condition for that decorator. Basically,
 * {@link ObserverAbort.Self} aborts the currently running behavior/task if the condition is not met and {@link ObserverAborts.LowerPriority} aborts the
 * currently running lower priority behavior/task when the condition is met. By default, {@link ObserverAborts.None} is used if you do not specify it.
 * @see {@link ObserverAborts} for additional details.
 *
 * The {@link BTT_Wait} is a fallback task when every other behaviors fail. This may be because your AI temporaily lost control by user actions, stuck or error
 * in your AI logic.
 */
export const BT_Root = new Selector({
    nodes: [
        IsSet(BT_Combat, "target", true, ObserverAborts.Both),
        IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, HasLowShield, true, ObserverAborts.LowerPriority),
        CanActivateAction(BTT_Taunt, Action.Taunt, true),
        IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BT_InvestigateNoise, "heardNoise", true, ObserverAborts.LowerPriority),
        BT_Patrol,
        BTT_Wait(1),
    ],
})
