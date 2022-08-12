import { ObserverAborts, Selector } from "behaviortree"
import { Action } from "enums"
import { CanActivateAction } from "@decorators/CanActivateAction"
import { Predicate } from "@decorators/Predicate"
import { BTT_SpecialAttack } from "@tasks/BTT_SpecialAttack"
import { BT_CloseCombat } from "@trees/combat/BT_CloseCombat"
import { BT_RangeCombat } from "@trees/combat/BT_RangeCombat"
import { Predicate_CloseCombat } from "@predicates/Predicate_CloseCombat"

/**
 * Behavior when AI can see the current target.
 *
 * This is where the main fighting logic is placed. Currently, it is broken into three sub-behaviors:
 *
 * - If the AI can activate special attack, it will perform the special attack to the target's last known location (@see {@link BTT_SpecialAttack}).
 * - Otherwise, if the target is close enough and AI can melee, it will enter close combat behavior (@see {@link BT_CloseCombat}).
 * - Otherwise, it will fallback to range combat behavior (@see {@link BT_RangeCombat}).
 *
 * You can modify this behavior tree as you may desire to customize the behavior of AI when it can see the current target.
 */
export const BT_CanSeeTarget = new Selector({
    nodes: [
        CanActivateAction(BTT_SpecialAttack("targetLastKnownLocation"), Action.SpecialAttack, true, ObserverAborts.LowerPriority),
        Predicate(BT_CloseCombat, Predicate_CloseCombat, true, ObserverAborts.Both),
        BT_RangeCombat,
    ],
})
