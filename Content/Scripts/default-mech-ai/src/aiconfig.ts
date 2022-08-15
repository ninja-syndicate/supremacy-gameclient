/**
 * Parameterized AI configuration values that can be tweaked without changing the overall structure of the AI behavior.
 * 
 * Recommended for non-programmers to get started.
 */
interface AIConfig {
    /** The range at which AI will enter the close combat behavior. */
    closeCombatEnterRange: number
    /** The range at which AI will exit the close combat behavior. Must be larger than {@link closeCombatEnterRange} to work properly. */
    closeCombatExitRange: number
    /** The threshold used for AI to think it has low shield. Must be in the range [0, 1]. */
    lowShieldThreshold: number
    /** The threshold used for AI to think it's in very low total health. Must be in the range [0, 1]. */
    veryLowTotalHealthThreshold: number
    /** The number of seconds a new damage stimulus will be remembered. NOTE: May end up keeping an array, so this may be removed in the future. */
    damageStimulusTimeout: number
    /** The maximum number of seconds to predict the target location before giving up. */
    predictionTimeout: number
    /** TODO: Implementation. This value does nothing currently. */
    tauntNoiseStimulusTimeout: number
    /** The number of seconds a new weapon noise will be remembered. NOTE: May end up keeping an array, so this may be removed in the future. */
    weaponNoiseStimulusTimeout: number
}

/** Default AI configuration. */
const DEFAULT_AI_CONFIG: AIConfig = {
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3500,
    lowShieldThreshold: 0.45,
    veryLowTotalHealthThreshold: 0.45,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5

}

/** Aggressive AI configuration. */
const AGGRESSIVE_AI_CONFIG: AIConfig = {
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3500,
    lowShieldThreshold: 0.2,
    veryLowTotalHealthThreshold: 0.2,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5
}

/** Conservative AI configuration. */
const CONSERVATIVE_AI_CONFIG: AIConfig = {
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3500,
    lowShieldThreshold: 0.6,
    veryLowTotalHealthThreshold: 0.6,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5
}

/** Current AI configuration. Change this to the desired AI config preset. */
export const CURRENT_AI_CONFIG: AIConfig = DEFAULT_AI_CONFIG
export const ENABLE_DEBUGGING: boolean = false