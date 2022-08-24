import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

/**
 * Checks if AI has low shield.
 *
 * @param blackboard
 * @returns true if the percentage of current shield to shield max is <= {@link CURRENT_AI_CONFIG.lowShieldThreshold} and false otherwise
 */
export const HasLowShield = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return self.shield / self.shieldMax <= CURRENT_AI_CONFIG.lowShieldThreshold
}
