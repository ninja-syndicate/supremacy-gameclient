import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

export const Predicate_FocusToWeaponNoise = (blackboard: AIBlackboard): boolean => {
    if (!blackboard.lastWeaponNoise) return false

    const timeDiff: number = blackboard.currentTime - blackboard.lastWeaponNoise.time
    if (timeDiff >= CURRENT_AI_CONFIG.weaponNoiseStimulusTimeout) return false

    return true
}
