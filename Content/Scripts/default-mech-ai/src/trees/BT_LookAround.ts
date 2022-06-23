import { Sequence } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { add, getForwardVector, multiply, rotateZ } from "../helper"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_Wait } from "../tasks/BTT_Wait"

// TODO: use Loop decorator
export const BT_LookAround = new Sequence({
    nodes: [
        BTT_SetValue(
            (blackboard: AIBlackboard) =>
                (blackboard.lookAtLocation = add(
                    blackboard.input.self.location,
                    multiply(rotateZ(getForwardVector(blackboard.input.self.rotation), 90), 1000),
                )),
        ),
        BTT_LookAt("lookAtLocation"),
        BTT_Wait(1),
        BTT_SetValue(
            (blackboard: AIBlackboard) =>
                (blackboard.lookAtLocation = add(
                    blackboard.input.self.location,
                    multiply(rotateZ(getForwardVector(blackboard.input.self.rotation), 90), 1000),
                )),
        ),
        BTT_LookAt("lookAtLocation"),
        BTT_Wait(1),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.lookAtLocation = undefined)),
        // BTT_Wait(50),
    ],
})
