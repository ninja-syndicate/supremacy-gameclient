import { AIBlackboard } from "@blackboards/blackboard"
import { Action, UserAction } from "enums"
import { AI } from "@root/index"

export const Predicate_CanActivateAction = (action: Action | UserAction) => (blackboard: AIBlackboard) => {
    return !!AI.CanActivateAction(action)
}
