import { AIBlackboard } from "@blackboards/blackboard"
import { Vector } from "types"
import { MovementMode } from "enums"
import { Predicate_InRange } from "@predicates/Predicate_InRange"

export const Predicate_SprintToEngagementByDistance =
    (location: Vector) =>
    (blackboard: AIBlackboard): boolean => {
        if (blackboard.currentMovementMode === MovementMode.Sprint) return false

        return !Predicate_InRange(blackboard.input.Self.Location, location, blackboard.optimalEngagementRange)(blackboard)
    }
