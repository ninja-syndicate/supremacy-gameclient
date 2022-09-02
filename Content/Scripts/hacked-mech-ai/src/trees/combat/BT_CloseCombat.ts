import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { WeaponTag } from "enums"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { Predicate_HasVeryLowTotalHealth, Predicate_TargetHasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"
import { BTT_MeleeAttack } from "@tasks/BTT_MeleeAttack"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_GetCover } from "@trees/BT_GetCover"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { Predicate_IsInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { AIBlackboard } from "@blackboards/blackboard"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { IsOutnumbered } from "@root/predicates/Predicate_IsOutnumbered"
import { BT_Strafe } from "@trees/BT_Strafe"
import { TargetHasMoreTotalHealth } from "@predicates/Predicate_TargetHasMoreTotalHealth"
import { ForceSuccess } from "@trees/helper/BT_Helper"
import { BT_UserAction } from "@trees/useraction/BT_UserAction"
import { BT_CloseCombatMovement } from "@trees/combat/BT_CloseCombatMovement"
import { Predicate_HasLowShield } from "@predicates/Predicate_HasLowShield"

// TODO: provide main and background properties for ParallelBackground
// TODO: Update code to actually reflect comment
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
        ForceSuccess(BT_UserAction),
        new Selector({
            nodes: [
                Predicate(BT_MoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
                IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
                Predicate(
                    BT_GetCover,
                    (blackboard: AIBlackboard) => Predicate_HasLowShield(blackboard) || Predicate_HasVeryLowTotalHealth(blackboard),
                    true,
                    ObserverAborts.LowerPriority,
                ),
                Predicate(
                    BT_CloseCombatMovement,
                    (blackboard: AIBlackboard) =>
                        !IsOutnumbered(blackboard) &&
                        !TargetHasMoreTotalHealth(blackboard) &&
                        Predicate_TargetHasVeryLowTotalHealth(blackboard) &&
                        !Predicate_HasVeryLowTotalHealth(blackboard),
                    true,
                    ObserverAborts.LowerPriority,
                ),
                BT_Strafe,
                BTT_Success,
            ],
        }),
    ],
})
