import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Checks if AI has very low total health (health + shield).
 *
 * @param blackboard
 * @returns true if the percentage of current total health to max total is <= 40% and false otherwise
 */
export const HasVeryLowTotalHealth = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= 0.4
}
