import { ObserverAborts, Selector } from "behaviortree"
import { AIBlackboard } from "../../blackboard"
import { IsSet } from "../../decorators/IsSet"
import { Predicate } from "../../decorators/Predicate"
import { HasLowShield } from "../../predicates/Predicate_HasLowShield"
import { BT_Camp } from "../BT_Camp"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_GetPickup } from "../BT_GetPickup"
import { BT_SearchTarget } from "../BT_SearchTarget"
import { BTT_Success } from "../../tasks/BTT_Success"

/**
 * The main combat behavior tree.
 *
 * This behavior represents what AI can do when it is in combat state. It is composed of the following sub-behavior trees:
 *
 * {@link BT_CanSeeTarget} if AI can see the current target and this behavior is where the actual fighting logic is placed
 * {@link BT_GetPickup} otherwise get to the pickup location if AI has any
 * {@link BT_Camp} - otherwise get to the cover location and camp if its shield is low
 * {@link BT_SearchTarget} - otherwise searches for the current target based on the target's last known location
 *
 * You can change this behavior to prioritise certain behaviors or anything you deem appropriate.
 */
export const BT_Combat = new Selector({
    nodes: [
        IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, HasLowShield, true, ObserverAborts.LowerPriority),
        // TODO: Handle damage stimulus location
        // TODO: Handle taunt
        Predicate(BT_SearchTarget, (blackboard: AIBlackboard) => !blackboard.canSeeTarget),
        // HACK: In case AI performs special attack, loses sight to target, movement action fails, and regains sight again, this task is
        // needed to ensure it can recover. Some predicate change is needed to remove this HACK.
        BTT_Success,
    ],
})
