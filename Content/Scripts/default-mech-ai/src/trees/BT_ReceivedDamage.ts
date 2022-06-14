import { Sequence } from "behaviortree"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_StopMoveTo } from "../tasks/BTT_StopMoveTo"
import { AIBlackboard } from "../blackboard"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { EQSArgument, EQSQueryType } from "enums"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { add, multiply } from "../helper"

/**
 * Behavior when AI receives damage.
 */
export const BT_ReceivedDamage = new Sequence({
    nodes: [
        BTT_StopMoveTo(),
        BTT_LookAt("damageStimulusFocalPoint"),
        BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) =>
            add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 10000)),
        ),
        BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
        BTT_SetFocalPoint("hiddenLocation"),
        BTT_MoveTo("hiddenLocation"),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.damageStimulusFocalPoint = undefined)),
    ],
})
