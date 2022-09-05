import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

export const Predicate_RecentlyLostTarget = (blackboard: AIBlackboard): boolean => {
    // For now, if it has no target, it hasn't lost target.
    if (!blackboard.target) return false
    if (blackboard.canSeeTarget) return false
    if (typeof blackboard.targetLostSightTime === "undefined") return false

    const elapsedTime: number = blackboard.currentTime - blackboard.targetLostSightTime
    return elapsedTime <= CURRENT_AI_CONFIG.sprintOnLostTargetTimeout
}
