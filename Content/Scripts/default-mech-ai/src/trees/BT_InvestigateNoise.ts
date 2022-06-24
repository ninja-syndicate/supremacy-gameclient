import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "../blackboard"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_EQSSetArgumentVector } from "../tasks/environment/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Behavior when the AI hears a noise.
 *
 * This behavior will cause AI to move to the noise location. Also, makes an environment query get a possible hidden location and moves to it
 * (@see {@link EQSQueryType.Hidden}). Note that the hidden environment query requires the argument {@link EQSArgument.TargetPredictedLocation} to be set before
 * it gets called and noise location is used for it.
 *
 * Currently, this behavior is not intended to be used when the AI is in combat state. If you want the AI to investigate noise while it is in combat state, you
 * may want to wrap around this behavior with {@link ParallelBackground} and have the background task execute {@link BT_SetFocal} to be able to respond to
 * stimulus such as damage while it is moving to the noise/hidden location.
 */
export const BT_InvestigateNoise = new Sequence({
    nodes: [
        BTT_SetFocalPoint("noiseLocation"),
        ForceSuccess(BTT_MoveTo("noiseLocation")), // Force success in case noise location is not navigable
        BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) => blackboard.noiseLocation),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
        BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
        BTT_SetFocalPoint("hiddenLocation"),
        BTT_MoveTo("hiddenLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
    ],
})
