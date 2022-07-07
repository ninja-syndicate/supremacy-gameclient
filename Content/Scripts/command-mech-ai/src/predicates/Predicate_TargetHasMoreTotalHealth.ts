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

    const selfTotalHealth = self.health + self.shield
    const targetTotalHealth = target.health + target.shield
    return targetTotalHealth > selfTotalHealth
}
