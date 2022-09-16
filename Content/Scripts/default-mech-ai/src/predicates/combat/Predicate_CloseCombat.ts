import { Vector } from "types"
import { AIBlackboard } from "@blackboards/blackboard"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"
import { distanceToVec } from "@root/helper"
import { Action } from "enums"

/**
 * Check if the AI should engage in close combat.
 *
 * Uses the distance to the target and whether it is already in close combat to decide whether it should engage/maintain close combat.
 *
 * @param blackboard
 * @returns true if the AI should engage in close combat and false otherwise
 */
export const Predicate_CloseCombat = (blackboard: AIBlackboard): boolean => {
    if (!blackboard.canMelee) return false
    if (!blackboard.canSeeTarget) return false
    if (typeof blackboard.targetLastKnownLocation === "undefined") return false
    if (typeof blackboard.targetLastKnownVelocity === "undefined") return false

    const selfLocation: Vector = blackboard.input.Self.Location
    const distToTarget: number = distanceToVec(selfLocation, blackboard.targetLastKnownLocation)
    const meleeStatus = blackboard.actionStatus.get(Action.MeleeAttack)
    if (meleeStatus !== undefined && meleeStatus) {
        return distToTarget <= CURRENT_AI_CONFIG.closeCombatExitRange
    }
    return distToTarget <= CURRENT_AI_CONFIG.closeCombatEnterRange
}
