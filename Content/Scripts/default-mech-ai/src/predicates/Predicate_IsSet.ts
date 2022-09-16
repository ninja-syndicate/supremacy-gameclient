import { AIBlackboard } from "@blackboards/blackboard"

export const Predicate_IsSet =
    (blackboardKey: keyof AIBlackboard, isSet: boolean = true) =>
    (blackboard: AIBlackboard): boolean => {
        return !!blackboard[blackboardKey] === isSet
    }
