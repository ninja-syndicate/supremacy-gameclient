import { AIBlackboard } from "../blackboard"

export const Predicate_FocusToWeaponNoise = (blackboard: AIBlackboard): boolean => {
    if (!blackboard.lastWeaponNoise) return false

    // TODO: Provide the time-limit as a globally configurable value.
    const timeDiff: number = blackboard.currentTime - blackboard.lastWeaponNoise.time
    if (timeDiff >= 5) return false

    return true
}
