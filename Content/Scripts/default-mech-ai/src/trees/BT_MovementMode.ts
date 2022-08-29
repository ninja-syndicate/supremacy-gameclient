import { Selector } from "behaviortree"
import { Predicate } from "@decorators/Predicate"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_SetMovementMode } from "@tasks/movement/BTT_SetMovementMode"
import { Predicate_TargetInRange } from "@predicates/Predicate_InRange"
import { MovementMode } from "enums"

export const Predicate_SprintByEngagementRange = (blackboard: AIBlackboard): boolean => {
    // If it's already sprinting, keep sprinting until it gets to optimal engagement range.
    if (blackboard.currentMovementMode === MovementMode.Sprint) {
        return !Predicate_TargetInRange(blackboard.optimalEngagementRange)(blackboard)
    }
    // If it's walking, only sprint if the AI itself is outside the ideal engagement range.
    return !Predicate_TargetInRange(blackboard.idealEngagementRange)(blackboard)
}

export const BT_MovementMode = new Selector({
    nodes: [Predicate(BTT_SetMovementMode(MovementMode.Sprint), Predicate_SprintByEngagementRange), BTT_SetMovementMode(MovementMode.Walk)],
})
