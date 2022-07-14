import { Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ForceSuccess } from "@decorators/ForceSuccess"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_SearchHiddenLocation } from "@trees/BT_SearchHiddenLocation"

/**
 * Behavior when AI heard a noise.
 *
 * This behavior will cause AI to move to the noise location. Also, makes an environment query get a possible hidden location based on the noise location and
 * moves to it (@see {@link EQSQueryType.Hidden} and {@link BT_SearchHiddenLocation}).
 *
 * Currently, this behavior is not intended to be used when AI is in combat state. If you want the AI to investigate noise while it is in combat state, you
 * may want to wrap around this behavior with {@link ParallelBackground} and have the background task execute {@link BT_SetFocal} to be able to respond to
 * stimulus such as damage while it is moving to the noise/hidden location.
 */
export const BT_InvestigateNoise = new Sequence({
    nodes: [
        BTT_SetFocalPoint("noiseLocation"),
        ForceSuccess(BTT_MoveTo("noiseLocation")), // Force success in case noise location is not navigable
        BT_SearchHiddenLocation("noiseLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
    ],
})
