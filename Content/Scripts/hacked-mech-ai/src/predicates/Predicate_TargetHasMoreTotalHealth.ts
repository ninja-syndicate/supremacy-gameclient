import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Checks if the current target has more total health (health + shield).
 *
 * @param blackboard
 * @returns true if the target has more total health and false otherwise
 */
export const TargetHasMoreTotalHealth = (blackboard: AIBlackboard) => {
    const self = blackboard.input.Self
    const target = blackboard.target
    if (target === null) return false

    const selfTotalHealthRatio = (self.Health + self.Shield) / (self.HealthMax + self.ShieldMax)
    const targetTotalHealthRatio = (target.Health + target.Shield) / (target.HealthMax + target.ShieldMax)
    return targetTotalHealthRatio > selfTotalHealthRatio
}

// NOTE: To be removed in the future by scoring function.
/**
 * Checks if the current target has way more total health (health + shield) ratio.
 *
 * @param blackboard
 * @returns true if the target has way more total health ratio and false otherwise
 */
export const TargetHasWayMoreTotalHealthRatio = (blackboard: AIBlackboard) => {
    const self = blackboard.input.Self
    const target = blackboard.target
    if (target === null) return false

    const selfTotalHealthRatio = (self.Health + self.Shield) / (self.HealthMax + self.ShieldMax)
    const targetTotalHealthRatio = (target.Health + target.Shield) / (target.HealthMax + target.ShieldMax)
    const ratioDiff: number = selfTotalHealthRatio - targetTotalHealthRatio
    if (ratioDiff >= 0) return false

    return ratioDiff + 0.2 <= 0
}
