import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

/**
 * Checks if AI has very low total health (health + shield).
 *
 * @param blackboard
 * @returns true if the percentage of current total health to max total is <= {@link CURRENT_AI_CONFIG.veryLowTotalHealthThreshold} and false otherwise
 */
export const Predicate_HasVeryLowTotalHealth = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= CURRENT_AI_CONFIG.veryLowTotalHealthThreshold
}
