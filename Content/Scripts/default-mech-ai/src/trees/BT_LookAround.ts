import { Parallel, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString, BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { AI } from ".."
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { add, getForwardVector, multiply, rotateZ } from "../helper"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_Wait } from "../tasks/BTT_Wait"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"

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
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.lookAtLocation = undefined)),
        // BTT_Wait(50),
    ],
})
