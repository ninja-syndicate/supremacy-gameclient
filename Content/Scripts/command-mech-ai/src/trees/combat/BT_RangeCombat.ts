import { ObserverAborts, Parallel, Selector, Sequence } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { HasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"
import { IsOutnumbered } from "@predicates/Predicate_IsOutnumbered"
import { IsOutnumberingEnemies } from "@predicates/Predicate_IsOutnumberingEnemies"
import { TargetHasMoreTotalHealth } from "@predicates/Predicate_TargetHasMoreTotalHealth"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_Shoot } from "@tasks/BTT_Shoot"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_GetCover } from "@trees/BT_GetCover"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { BT_Strafe } from "@trees/BT_Strafe"
import { BT_MoveToCommand } from "../BT_MoveToCommand"
import { BT_Patrol } from "../BT_Patrol"

// TODO: Separate ParallelBackground into main and background tasks properties.
// TODO: Replace with ForceSuccess decorator? and replace comments
/**
 * Behavior when AI is in range combat.
 *
 * The range combat behavior is a parallel task that executes the main and background tasks and keep running background tasks until the main task completes
 * (@see {@link ParallelBackground}). Currently, the main task is the Parallel node which causes the weapons attached to the left and right arm to shoot. The
 * background tasks are the {@link BT_SetFocal} and the selector beneath it. {@link BT_SetFocal} sets the focal point to the appropriate place depending on what
 * the AI has on its blackboard (@see {@link BT_SetFocal}). The selector selects most appropriate move to location based on the current state. You can customize
 * these behaviors as you wish.
 *
 * The {@link BTT_Success} at the end forces the selector to succeed when the other behaviors fail (e.g. movement/env query fail) which will keep
 * {@link BT_RangeCombat} running.
 *
 * Note that {@link BTT_Shoot} will never complete or fail unless there are no ammo or the weapon is not shootable, so this behavior will continue running until
 * it is aborted by {@link ObserverAborts}.
 */
export const BT_RangeCombat = new ParallelBackground({
    nodes: [
        // TODO: Maybe make it ParallelSelector when ammo support is needed
        new Parallel({
            nodes: [BTT_Shoot(WeaponTag.PrimaryLeftArm), BTT_Shoot(WeaponTag.PrimaryRightArm)],
        }),
        BT_SetFocal,
        new Selector({
            nodes: [
                IsSet(BT_MoveToCommand, "isCommanded", true, ObserverAborts.Both),
                IsSet(BT_Patrol, "moveCommandLocation", true),
                BTT_Success
            ],
        }),
    ],
})
