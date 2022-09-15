import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

/**
 * Checks if AI has very low total health (health + shield).
 *
 * @param blackboard
 * @returns true if the percentage of current total health to max total is <= {@link CURRENT_AI_CONFIG.veryLowTotalHealthThreshold} and false otherwise
 */
export const Predicate_HasVeryLowTotalHealth = (blackboard: AIBlackboard) => {
    let self = blackboard.input.Self
    return (self.Health + self.Shield) / (self.HealthMax + self.ShieldMax) <= CURRENT_AI_CONFIG.veryLowTotalHealthThreshold
}

export const Predicate_TargetHasVeryLowTotalHealth = (blackboard: AIBlackboard) => {
    const target = blackboard.target
    if (target === null) return false

    return (target.Health + target.Shield) / (target.HealthMax + target.ShieldMax) <= CURRENT_AI_CONFIG.veryLowTotalHealthThreshold
}
