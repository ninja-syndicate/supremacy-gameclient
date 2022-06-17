import { Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { AIBlackboard } from "../blackboard"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { EQSArgument, EQSQueryType } from "enums"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { ForceSuccess } from "../decorators/ForceSuccess"

/**
 * Investigate noise behavior.
 */
export const BT_InvestigateNoise = new Sequence({
    nodes: [
        BTT_SetFocalPoint("noiseLocation"),
        ForceSuccess(BTT_MoveTo("noiseLocation")),
        BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) => blackboard.noiseLocation),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
        BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
        BTT_SetFocalPoint("hiddenLocation"),
        BTT_MoveTo("hiddenLocation"),
    ],
})
