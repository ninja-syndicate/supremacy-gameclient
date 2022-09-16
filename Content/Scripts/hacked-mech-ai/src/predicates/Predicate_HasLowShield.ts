import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

/**
 * Checks if AI has low shield.
 *
 * @param blackboard
 * @returns true if the percentage of current shield to shield max is <= {@link CURRENT_AI_CONFIG.lowShieldThreshold} and false otherwise
 */
export const Predicate_HasLowShield = (blackboard: AIBlackboard) => {
    const self = blackboard.input.Self
    if (self.ShieldMax <= 0) return false

    return self.Shield / self.ShieldMax <= CURRENT_AI_CONFIG.lowShieldThreshold
}
