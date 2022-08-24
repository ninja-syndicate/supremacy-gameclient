import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

export const Predicate_FocusToPredictedLocation = (blackboard: AIBlackboard): boolean => {
    // Check undefines.
    if (typeof blackboard.targetPredictedLocation === "undefined") return false

    // TODO: Provide the time-limit as a globally configurable value.
    const timeDiff: number = blackboard.currentTime - blackboard.targetLostSightTime
    if (timeDiff >= CURRENT_AI_CONFIG.predictionTimeout) return false

    return true
}
