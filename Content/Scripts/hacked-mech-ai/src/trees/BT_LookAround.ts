import { Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { add, getForwardVector, multiply, rotateZ } from "../helper"
import { BTT_LookAt } from "@tasks/BTT_LookAt"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_Wait } from "@tasks/BTT_Wait"

// TODO: Use loop decorator.
/**
 * Look around behavior.
 *
 * Makes the AI look at 90 degrees right from the current rotation twice.
 * Intended to be used to detect friendlies and enemies near the AI.
 */
export const BT_LookAround = new Sequence({
    nodes: [
        BTT_SetValue(
            (blackboard: AIBlackboard) =>
                (blackboard.lookAtLocation = add(
                    blackboard.input.Self.Location,
                    multiply(rotateZ(getForwardVector(blackboard.input.Self.Rotation), 90), 1000),
                )),
        ),
        BTT_LookAt("lookAtLocation"),
        BTT_Wait(1),
        BTT_SetValue(
            (blackboard: AIBlackboard) =>
                (blackboard.lookAtLocation = add(
                    blackboard.input.Self.Location,
                    multiply(rotateZ(getForwardVector(blackboard.input.Self.Rotation), 90), 1000),
                )),
        ),
        BTT_LookAt("lookAtLocation"),
        BTT_Wait(1),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.lookAtLocation = undefined)),
    ],
})
