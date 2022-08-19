import { AIBlackboard } from "@blackboards/blackboard"
import { Action } from "enums"
import { AI } from "@root/index"

export const Predicate_CanActivateAction = (action: Action) => (blackboard: AIBlackboard) => {
    return !!AI.CanActivateAction(action)
}
