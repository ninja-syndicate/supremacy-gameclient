import { ObserverAborts, Selector } from "behaviortree"
import { AIBlackboard } from "../../blackboard"
import { IsSet } from "../../decorators/IsSet"
import { Predicate } from "../../decorators/Predicate"
import { HasLowShield } from "../../predicates/Predicate_HasLowShield"
import { BT_Camp } from "../BT_Camp"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_GetPickup } from "../BT_GetPickup"
import { BT_SearchTarget } from "../BT_SearchTarget"

export const BT_Combat = new Selector({
    nodes: [
        IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, HasLowShield, true, ObserverAborts.LowerPriority),
        /*
        Predicate(
            BT_ReceivedDamage,
            (blackboard: AIBlackboard) => !blackboard.canSeeTarget && blackboard.damageStimulusFocalPoint !== undefined && !blackboard.isLastDamageFromTarget,
            true,
            ObserverAborts.LowerPriority,
        ),
        */
        // CanActivateAction(BTT_Taunt, Action.Taunt, true),
        Predicate(BT_SearchTarget, (blackboard: AIBlackboard) => !blackboard.canSeeTarget),
    ],
})
