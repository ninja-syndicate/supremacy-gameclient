import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Checks if AI has low shield.
 *
 * @param blackboard
 * @returns true if the percentage of current shield to shield max is <= 40% and false otherwise
 */
export const HasLowShield = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return self.shield / self.shieldMax <= 0.4
}
