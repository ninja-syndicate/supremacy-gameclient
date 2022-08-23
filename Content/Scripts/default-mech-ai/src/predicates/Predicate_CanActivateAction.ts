import { AIBlackboard } from "@blackboards/blackboard"
import { Action, UserAction } from "enums"
import { AI } from "@root/index"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

export const Predicate_CanActivateAction = (action: Action | UserAction) => (blackboard: AIBlackboard) => {
    return !!AI.CanActivateAction(action)
}

/**
 *
 */
export const Predicate_CanActivateUserAction = (userAction) => (blackboard: AIBlackboard) => {
    if (!CURRENT_AI_CONFIG.enableUserAction) return false

    return !!AI.CanActivateAction(userAction)
}
