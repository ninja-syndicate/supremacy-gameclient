import { AIBlackboard } from "@blackboards/blackboard"
import { Action } from "enums"

/**
 * Checks if the AI is using the specified action.
 *
 * @param blackboard
 * @returns true if the AI is using the specified action and false otherwise.
 */
export const Predicate_IsUsingAction = (action: Action) => (blackboard: AIBlackboard) => {
    const isUsingAction = blackboard.actionStatus.get(action)
    return isUsingAction !== undefined && isUsingAction
}
