import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "../blackboard"
import { add, multiply } from "../helper"
import { BTT_EQSSetArgumentVector } from "../tasks/environment/BTT_EQSSetArgument"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_StopMoveTo } from "../tasks/movement/BTT_StopMoveTo"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Behavior when AI receives damage.
 */
export const BT_ReceivedDamage = new Sequence({
    nodes: [
        BTT_StopMoveTo,
        BTT_LookAt("damageStimulusFocalPoint"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.damageStimulusFocalPoint = undefined)),
        BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) =>
            add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 10000)),
        ),
        BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
        BTT_SetFocalPoint("hiddenLocation"),
        BTT_MoveTo("hiddenLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
    ],
})
