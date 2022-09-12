import { AIBlackboard } from "@blackboards/blackboard"
import { Action } from "enums"
import { Predicate_CanActivateAction } from "@predicates/Predicate_CanActivateAction"
import { Predicate_HasLowShield } from "./Predicate_HasLowShield"

export const Predicate_UseTaunt = (blackboard: AIBlackboard): boolean => {
    if (Predicate_HasLowShield(blackboard)) return false
    if (!Predicate_CanActivateAction(Action.Taunt)(blackboard)) return false

    return true
}
