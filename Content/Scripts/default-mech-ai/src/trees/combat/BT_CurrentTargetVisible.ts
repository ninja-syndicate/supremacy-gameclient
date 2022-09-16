import { Selector } from "behaviortree"
import { BTT_SpecialAttack } from "@tasks/BTT_SpecialAttack"
import { BT_Combat } from "@root/trees/combat/BT_Combat"

/**
 * Behavior when AI can see the current target.
 *
 * This is where the main fighting logic is placed. Currently, it is broken into three sub-behaviors:
 *
 * - If the AI can activate special attack, it will perform the special attack to the target's last known location (@see {@link BTT_SpecialAttack}).
 * - Otherwise, if {@link Predicate_CloseCombat} is satisfied, it will enter close combat behavior (@see {@link BT_CloseCombat}).
 * - Otherwise, it will fallback to range combat behavior (@see {@link BT_Combat}).
 *
 * You can modify this behavior tree as you may desire to customize the behavior of AI when it can see the current target.
 */
export const BT_CurrentTargetVisible = new Selector({
    nodes: [BT_Combat],
})
