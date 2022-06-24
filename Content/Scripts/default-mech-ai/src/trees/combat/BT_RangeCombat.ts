import { ObserverAborts, Parallel, Selector } from "behaviortree"
import { WeaponTag } from "../../../../types/enums"
import { AIBlackboard } from "../../blackboard"
import { ParallelBackground } from "../../branches/ParallelBackground"
import { IsSet } from "../../decorators/IsSet"
import { Predicate } from "../../decorators/Predicate"
import { HasVeryLowTotalHealth } from "../../predicates/Predicate_HasVeryLowTotalHealth"
import { IsOutnumbered } from "../../predicates/Predicate_IsOutnumbered"
import { IsOutnumberingEnemies } from "../../predicates/Predicate_IsOutnumberingEnemies"
import { TargetHasMoreTotalHealth } from "../../predicates/Predicate_TargetHasMoreTotalHealth"
import { BTT_MoveTo } from "../../tasks/movement/BTT_MoveTo"
import { BTT_Shoot } from "../../tasks/BTT_Shoot"
import { BTT_Success } from "../../tasks/BTT_Success"
import { BT_GetCover } from "../BT_GetCover"
import { BT_GetPickup } from "../BT_GetPickup"
import { BT_SetFocal } from "../BT_SetFocal"
import { BT_Strafe } from "../BT_Strafe"

// TODO: Separate ParallelBackgorund into main and backgorund tasks properties.

/**
 * Behavior when the AI is in range combat.
 *
 * The range combat behavior is basically a parallel task that executes main and background tasks and keep running background tasks until the main task
 * completes (@see {@link ParallelBackground}). Currently, the main task is the Parallel node which causes the weapons attached to the left and right arm to
 * shoot. The background tasks are the BT_SetFocal and the selector beneath it. It will set the focal point to the appropriate place depending on what the AI
 * has on its blackboard. The selector , in case movement fails, BTT_Success (TODO: Replace with ForceSuccess decorator?) will make the behavior keep running.
 *
 * because the BTT_Shoot will never complete or fail unelss there are no ammo (or not shootable), this behavior will continue running until it is aborted by
 * {@link ObserverAborts}.
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
                IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
                Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.LowerPriority),
                Predicate(
                    // TODO: This should ideally be getting closer, not directly to target.
                    BTT_MoveTo("targetLastKnownLocation"),
                    (blackboard: AIBlackboard) => (!TargetHasMoreTotalHealth(blackboard) && !IsOutnumbered(blackboard)) || IsOutnumberingEnemies(blackboard),
                    true,
                    ObserverAborts.Both,
                ),
                BT_Strafe,
                BTT_Success,
            ],
        }),
    ],
})
