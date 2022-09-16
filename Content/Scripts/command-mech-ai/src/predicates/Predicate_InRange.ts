import { AIBlackboard } from "@blackboards/blackboard"
import { distanceToVec } from "@root/helper"
import { Vector } from "types"

/**
 * Checks if the two locations are within the specified range.
 *
 * @param range the range to check for
 * @returns true if the distance between two locations are within the range and false otherwise.
 */
export const Predicate_InRange = (v1: Vector, v2: Vector, range: number) => (blackboard: AIBlackboard) => {
    return distanceToVec(v1, v2) <= range
}

/**
 * Checks if the target is within the specified range.
 *
 * @param range the range to check for
 * @returns true if the distance to target is within the range and false otherwise.
 */
export const Predicate_TargetInRange = (range: number) => (blackboard: AIBlackboard) => {
    if (blackboard.target === null) return false
    if (!blackboard.canSeeTarget) return false

    return Predicate_InRange(blackboard.input.Self.Location, blackboard.target.Location, range)(blackboard)
}
