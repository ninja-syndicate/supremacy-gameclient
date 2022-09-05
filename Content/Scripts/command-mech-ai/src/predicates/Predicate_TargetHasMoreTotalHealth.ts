import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Checks if the current target has more total health (health + shield).
 *
 * @param blackboard
 * @returns true if the target has more total health and false otherwise
 */
export const TargetHasMoreTotalHealth = (blackboard: AIBlackboard) => {
    const self = blackboard.input.self
    const target = blackboard.target
    if (target === null) return false

    const selfTotalHealthRatio = (self.health + self.shield) / (self.healthMax + self.shieldMax)
    const targetTotalHealthRatio = (target.health + target.shield) / (target.healthMax + target.shieldMax)
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
    const self = blackboard.input.self
    const target = blackboard.target
    if (target === null) return false

    const selfTotalHealthRatio = (self.health + self.shield) / (self.healthMax + self.shieldMax)
    const targetTotalHealthRatio = (target.health + target.shield) / (target.healthMax + target.shieldMax)
    const ratioDiff: number = selfTotalHealthRatio - targetTotalHealthRatio
    if (ratioDiff >= 0) return false

    return ratioDiff + 0.2 <= 0
}
