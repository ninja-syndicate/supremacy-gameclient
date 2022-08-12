import { ObserverAborts, Selector } from "behaviortree"
import { WeaponTag } from "enums"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { HasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"
import { BTT_MeleeAttack } from "@tasks/BTT_MeleeAttack"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_GetCover } from "@trees/BT_GetCover"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { BT_CloseStrafe } from "@trees/BT_CloseStrafe"
import { TargetInRange } from "@predicates/Predicate_InRange"
import { Predicate_IsInsideBattleZone, Predicate_IsTargetInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { AIBlackboard } from "@blackboards/blackboard"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"

// TODO: provide main and background properties for ParallelBackground
/**
 * Behavior when the AI is in close combat.
 *
 * Similar to {@link BT_RangeCombat}, this close combat behavior is a {@link ParallelBackground} branch node that executes the main task and keep running
 * background tasks until the main task completes (@see {@link ParallelBackground}). In this case, the main task activates the melee weapon and background tasks
 * set the focal point and move to location to most appropriate target/location based on the current blackboard state. You can customize these behaviors as you
 * wish.
 *
 * As with {@link BT_RangeCombat}, {@link BTT_Success} at the end forces the selector to succeed when the other behaviors fail (e.g. movement/env query fail)
 * which will keep {@link BT_CloseCombat} running and this behavior will continue running until it is aborted by {@link ObserverAborts}.
 */
export const BT_CloseCombat = new ParallelBackground({
    nodes: [
        // Main task
        BTT_MeleeAttack(WeaponTag.Melee),

        // Background tasks
        BTT_SetFocalPoint("target"),
        new Selector({
            nodes: [
                Predicate(BT_MoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
                IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
                Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.LowerPriority),
                Predicate(
                    BTT_MoveTo("targetLastKnownLocation", true),
                    (blackboard: AIBlackboard) => !TargetInRange(2000)(blackboard) && Predicate_IsTargetInsideBattleZone(blackboard),
                    true,
                    ObserverAborts.LowerPriority,
                ),
                BT_CloseStrafe,
                BTT_Success,
            ],
        }),
    ],
})
