import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"

export const Predicate_FocusToDamage = (blackboard: AIBlackboard): boolean => {
    // Check undefines.
    if (typeof blackboard.damageStimulusFocalPoint === "undefined") return false
    if (typeof blackboard.damageInstigatorHash === "undefined") return false

    // Always look at the damage stimulus focal point if it has no target.
    // TODO: Don't look if damage instigator hash === nulled target's hash.
    if (blackboard.target === null) return true

    // Don't look at the damage stimulus if it can see the current target.
    // TODO: Consider damage?
    if (blackboard.canSeeTarget) return false

    if (blackboard.damageStimulusTime <= blackboard.targetLostSightTime) {
        // If the damage stimulus is old, don't focus to it.
        const timeDiff = blackboard.currentTime - blackboard.damageStimulusTime
        if (timeDiff >= CURRENT_AI_CONFIG.damageStimulusTimeout) return false

        return blackboard.damageInstigatorHash !== blackboard.target.hash
    } else return true
}
