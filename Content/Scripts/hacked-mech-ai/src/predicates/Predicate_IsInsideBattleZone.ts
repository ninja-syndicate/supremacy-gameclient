import { AI } from "@root/index"
import { AIBlackboard } from "@blackboards/blackboard"
import { Vector } from "types"
import { IsVector } from "@root/utils"

/**
 * Checks if the location is inside the battle zone.
 *
 * @param blackboard
 * @returns true if the location is inside the battle zone and false otherwise
 */
export const Predicate_IsLocationInsideBattleZone =
    (blackboardKey: keyof AIBlackboard) =>
    (blackboard: AIBlackboard): boolean => {
        const value = blackboard[blackboardKey]
        if (!value) return false
        if (!IsVector(value)) return false

        return AI.IsInsideBattleZone(value)
    }

/**
 * Checks if the current target is inside the battle zone.
 *
 * @param blackboard
 * @returns true if the target is inside the battle zone and false otherwise
 */
export const Predicate_IsTargetInsideBattleZone = (blackboard: AIBlackboard): boolean => {
    if (!blackboard.target) return false

    const targetLocation: Vector = blackboard.target.location
    return AI.IsInsideBattleZone(targetLocation)
}

/**
 * Checks if the AI is inside the battle zone.
 *
 * @param blackboard
 * @returns true if the AI is inside the battle zone and false otherwise
 */
export const Predicate_IsInsideBattleZone = (blackboard: AIBlackboard): boolean => {
    const location: Vector = blackboard.input.self.location
    return AI.IsInsideBattleZone(location)
}
