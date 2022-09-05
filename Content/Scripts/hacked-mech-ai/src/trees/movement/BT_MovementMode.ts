import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { MovementMode } from "enums"
import { BTT_SetMovementMode } from "@tasks/movement/BTT_SetMovementMode"
import { ForceSuccess } from "@trees/helper/BT_Helper"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { Predicate_SprintToEngagementByDistance } from "@predicates/combat/Predicate_SprintToEngagement"
import { Predicate } from "@decorators/Predicate"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

// TODO: Support restore previous movement mode at end option.
// TODO: Add a check if the specified movement mode is available.
// TODO: Make custom move fail if specified movement mode isn't available and provide custom BT for choosing the best one.
/**
 *
 * @param movementMode
 * @returns
 */
const WrappedTask_CustomModeMoveTo =
    (movementMode: MovementMode) =>
    (blackboardKey: keyof AIBlackboard, observeBlackboardKey: boolean = false) =>
        new Sequence({
            nodes: [
                ForceSuccess(BTT_SetMovementMode(movementMode)),
                BTT_MoveTo(blackboardKey, observeBlackboardKey),
                ForceSuccess(BTT_SetMovementMode(CURRENT_AI_CONFIG.defaultMovementMode)),
            ],
        })

/**
 * Behavior that uses the specified movement mode for moving to the specified location.
 */
export const BT_WalkMoveTo = WrappedTask_CustomModeMoveTo(MovementMode.Walk)
export const BT_SprintMoveTo = WrappedTask_CustomModeMoveTo(MovementMode.Sprint)
export const BT_DefaultMoveTo = WrappedTask_CustomModeMoveTo(CURRENT_AI_CONFIG.defaultMovementMode)

/**
 * Behavior that does sprinting if the target is not within engagement range.
 * Uses the normal movement mode otherwise.
 *
 * @param blackboardKey
 * @param observeBlackboardKey
 * @returns
 */
export const BT_MoveByDistanceToTarget = (blackboardKey: keyof AIBlackboard, observeBlackboardKey: boolean = false) =>
    new Selector({
        nodes: [
            Predicate(
                BT_SprintMoveTo(blackboardKey, observeBlackboardKey),
                (blackboard: AIBlackboard) => blackboard.target && Predicate_SprintToEngagementByDistance(blackboard.target.location)(blackboard),
                true,
                ObserverAborts.LowerPriority, // Can be set to ObserverAborts.Both if we want to immediately switch movement mode.
            ),
            BT_DefaultMoveTo(blackboardKey, observeBlackboardKey),
        ],
    })
