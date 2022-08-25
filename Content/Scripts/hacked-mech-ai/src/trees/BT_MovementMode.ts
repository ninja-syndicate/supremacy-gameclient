import { Selector } from "behaviortree"
import { Predicate } from "@decorators/Predicate"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_SetMovementMode } from "@tasks/movement/BTT_SetMovementMode"
import { Predicate_TargetInRange } from "@predicates/Predicate_InRange"
import { MovementMode } from "enums"

export const BT_MovementMode = new Selector({
    nodes: [
        Predicate(
            BTT_SetMovementMode(MovementMode.Sprint),
            (blackboard: AIBlackboard) => !Predicate_TargetInRange(blackboard.idealEngagementRange)(blackboard),
        ),
        BTT_SetMovementMode(MovementMode.Walk),
    ],
})
