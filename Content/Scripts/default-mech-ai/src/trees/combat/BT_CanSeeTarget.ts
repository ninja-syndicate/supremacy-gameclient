import { ObserverAborts, Selector } from "behaviortree"
import { Action } from "enums"
import { AIBlackboard } from "../../blackboard"
import { CanActivateAction } from "../../decorators/CanActivateAction"
import { Predicate } from "../../decorators/Predicate"
import { distanceToVec } from "../../helper"
import { BTT_SpecialAttack } from "../../tasks/BTT_SpecialAttack"
import { BT_CloseCombat } from "./BT_CloseCombat"
import { BT_RangeCombat } from "./BT_RangeCombat"

/**
 * Behavior when AI can see the current target.
 *
 * Currently, this behavior is broken into three sub-behaviors.
 * - If the AI can activate special attack, it will perform the attack to the target's last known location (@see {@link BTT_SpecialAttack}).
 * - Otherwise, if the target is close enough and the AI can melee, it will enter close combat behavior (@see {@link BT_CloseCombat}).
 * - Otherwise, it will fallback to range combat behavior (@see {@link BT_RangeCombat}).
 *
 * You can modify this behavior tree as you may desire to customize the behavior of AI when it can see the current target.
 */
export const BT_CanSeeTarget = new Selector({
    nodes: [
        CanActivateAction(BTT_SpecialAttack("targetLastKnownLocation"), Action.SpecialAttack, true, ObserverAborts.LowerPriority),
        Predicate(
            BT_CloseCombat,
            (blackboard: AIBlackboard) =>
                blackboard.canMelee &&
                blackboard.targetLastKnownLocation !== undefined &&
                distanceToVec(blackboard.input.self.location, blackboard.targetLastKnownLocation) <= 4000,
            true,
            ObserverAborts.Both,
        ),
        BT_RangeCombat,
    ],
})
