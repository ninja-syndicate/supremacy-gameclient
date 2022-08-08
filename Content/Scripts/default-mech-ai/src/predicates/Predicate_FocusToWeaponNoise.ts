import { AIBlackboard } from "@blackboards/blackboard"

export const Predicate_FocusToWeaponNoise = (blackboard: AIBlackboard): boolean => {
    if (blackboard.lastWeaponNoise === null) return false

    // TODO: Provide the time-limit as a globally configurable value.
    const timeDiff: number = blackboard.currentTime - blackboard.targetLostSightTime
    if (timeDiff >= 10) return false

    return true
}
