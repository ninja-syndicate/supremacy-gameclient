/**
 * Parameterized AI configuration values that can be tweaked without changing the overall structure of the AI behavior.
 *
 * Recommended for non-programmers to get started.
 */
// TODO: Update README documentation to point to this.
interface AIConfig {
    /** A flag that can be used to turn on/off automatic user action abilities for AI. You would only want to turn this off if you want to take control. */
    enableUserAction: boolean
    /** The multiplier applied to the optimalEngagementRange to calculate idealEngagementRange for the shootable weapons. */
    optimalRangeMultiplier: number
    /** The range at which AI will enter the close combat behavior. */
    closeCombatEnterRange: number
    /** The range at which AI will exit the close combat behavior. Must be larger than {@link closeCombatEnterRange} to work properly. */
    closeCombatExitRange: number
    /**
     * The range at which AI will move towards the current target instead of strafing when it's in close combat behavior. This value must be less than
     * {@link closeCombatExitRange}.
     */
    closeCombatKeepRange: number
    /** The threshold used for AI to think it has low shield. Must be in the range [0, 1]. */
    lowShieldThreshold: number
    /** The threshold used for AI to think it's in very low total health. Must be in the range [0, 1]. */
    veryLowTotalHealthThreshold: number
    /** The number of seconds a new damage stimulus will be remembered. NOTE: May end up keeping an array, so this may be removed in the future. */
    damageStimulusTimeout: number
    /** The maximum number of seconds to predict the target location before giving up. */
    predictionTimeout: number
    /** 
     * The prediction update interval. Making this value smaller may update target's predicted location more frequently, but its focal point update won't be
     * smooth. 
     */
    predictionUpdateInterval: number
    /** TODO: Implementation. This value does nothing currently. */
    tauntNoiseStimulusTimeout: number
    /** The number of seconds a new weapon noise will be remembered. NOTE: May end up keeping an array, so this may be removed in the future. */
    weaponNoiseStimulusTimeout: number
    /**
     * The maximum distance to consider by sight. This is used for filtering out far-away targets.
     * Note that {@link Perception.sight} is filtered by maximum vision range before it gets passed to the {@link BrainInput}.
     */
    sightMaxDistance: number
}

/** Default AI configuration. */
const DEFAULT_AI_CONFIG: AIConfig = {
    enableUserAction: false,
    optimalRangeMultiplier: 1.1,
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3250,
    closeCombatKeepRange: 2000,
    lowShieldThreshold: 0.5,
    veryLowTotalHealthThreshold: 0.5,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    predictionUpdateInterval: 3,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5,
    sightMaxDistance: 50000,
}

/** Aggressive AI configuration. */
const AGGRESSIVE_AI_CONFIG: AIConfig = {
    enableUserAction: true,
    optimalRangeMultiplier: 1.1,
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3250,
    closeCombatKeepRange: 2000,
    lowShieldThreshold: 0.2,
    veryLowTotalHealthThreshold: 0.2,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    predictionUpdateInterval: 3,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5,
    sightMaxDistance: 50000,
}

/** Conservative AI configuration. */
const CONSERVATIVE_AI_CONFIG: AIConfig = {
    enableUserAction: true,
    optimalRangeMultiplier: 1.1,
    closeCombatEnterRange: 2250,
    closeCombatExitRange: 3250,
    closeCombatKeepRange: 2000,
    lowShieldThreshold: 0.6,
    veryLowTotalHealthThreshold: 0.6,
    damageStimulusTimeout: 10,
    predictionTimeout: 10,
    predictionUpdateInterval: 3,
    tauntNoiseStimulusTimeout: 30,
    weaponNoiseStimulusTimeout: 5,
    sightMaxDistance: 50000,
}

/** Current AI configuration. Change this to the desired AI config preset. */
export const CURRENT_AI_CONFIG: AIConfig = DEFAULT_AI_CONFIG
export const ENABLE_DEBUGGING: boolean = false
