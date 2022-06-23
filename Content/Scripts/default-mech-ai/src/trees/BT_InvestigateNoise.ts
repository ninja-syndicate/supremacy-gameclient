import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "../blackboard"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Investigate noise behavior.
 */
export const BT_InvestigateNoise = new Sequence({
    nodes: [
        BTT_SetFocalPoint("noiseLocation"),
        ForceSuccess(BTT_MoveTo("noiseLocation")),
        BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) => blackboard.noiseLocation),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
        BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
        BTT_SetFocalPoint("hiddenLocation"),
        BTT_MoveTo("hiddenLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
    ],
})
