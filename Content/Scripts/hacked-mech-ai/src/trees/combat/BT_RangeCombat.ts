import { ObserverAborts, Parallel, Selector, Sequence } from "behaviortree"
import { UserAction, WeaponTag } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { Predicate_HasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"
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
import { BT_CloseStrafe } from "@trees/BT_CloseStrafe"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"
import { Predicate_IsInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_MovementMode } from "@trees/BT_MovementMode"
import { ForceSuccess } from "@decorators/ForceSuccess"
import { BT_UserAction } from "@trees/useraction/BT_UserAction"

// TODO: Separate ParallelBackground into main and background tasks properties.
// TODO: Replace with ForceSuccess decorator? and replace comments
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
        BTT_SetFocalPoint("target"),
        // BT_MovementMode,
        ForceSuccess(BT_UserAction),
        new Selector({
            nodes: [
                Predicate(BT_MoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
                IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
                Predicate(BT_GetCover, Predicate_HasVeryLowTotalHealth, true, ObserverAborts.LowerPriority),
                Predicate(
                    new Selector({
                        nodes: [BT_CloseStrafe, BTT_MoveTo("targetLastKnownLocation")],
                    }),
                    (blackboard: AIBlackboard) => !TargetHasMoreTotalHealth(blackboard),
                    true,
                    ObserverAborts.Both,
                ),
                BT_Strafe,
                BTT_Success,
            ],
        }),
    ],
})
