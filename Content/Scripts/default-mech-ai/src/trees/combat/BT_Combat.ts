import { ObserverAborts, Selector } from "behaviortree"
import { WeaponTag } from "enums"
import { ParallelBackground } from "@branches/ParallelBackground"
import { Predicate } from "@decorators/Predicate"
import { BTT_Shoot } from "@root/tasks/weapon/BTT_Shoot"
import { BTT_Success } from "@tasks/BTT_Success"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { ForceSuccess } from "@trees/helper/BT_Helper"
import { BT_UserAction } from "@trees/useraction/BT_UserAction"
import { BT_CombatMovement } from "@trees/combat/BT_CombatMovement"
import { Predicate_HasAmmoByTag } from "@predicates/combat/Predicate_HasAmmo"
import { conjunct } from "@predicates/Functional"
import { Predicate_UseSpecialAttack } from "@predicates/combat/Predicate_UseSpecialAttack"
import { BT_PrimaryAttack } from "@trees/attack/BT_PrimaryAttack"
import { BT_FireRocketPod } from "@trees/attack/BT_SecondaryAttack"

// TODO: Separate ParallelBackground into main and background tasks properties.
// TODO: Update code to actually reflect comment
/**
 * Behavior when AI is in range combat.
 *
 * The range combat behavior is a parallel task that executes the main and background tasks and keep running background tasks until the main task completes
 * (@see {@link ParallelBackground}). Currently, the main task is the Parallel node which causes the weapons attached to the left and right arm to shoot. The
 * background tasks are the {@link BTT_SetFocalPoint("target")} and the selector beneath it. {@link BTT_SetFocalPoint("target")} sets the focal point to the
 * target. The selector selects most appropriate move to location based on the current state. You can customize these behaviors as you wish.
 *
 * The {@link BTT_Success} at the end forces the selector to succeed when the other behaviors fail (e.g. movement/env query fail) which will keep
 * {@link BT_Combat} running.
 *
 * Note that {@link BTT_Shoot} will never complete or fail unless there are no ammo or the weapon is not shootable, so this behavior will continue running until
 * it is aborted by {@link ObserverAborts}.
 */
export const BT_Combat = new Selector({
    nodes: [
        Predicate(BT_FireRocketPod, conjunct(Predicate_UseSpecialAttack, Predicate_HasAmmoByTag(WeaponTag.Secondary)), true, ObserverAborts.LowerPriority),
        new ParallelBackground({
            nodes: [
                // Main task
                BT_PrimaryAttack,

                // Background tasks
                BTT_SetFocalPoint("target"),
                ForceSuccess(BT_UserAction),
                ForceSuccess(BT_CombatMovement),
            ],
        }),
    ],
})
