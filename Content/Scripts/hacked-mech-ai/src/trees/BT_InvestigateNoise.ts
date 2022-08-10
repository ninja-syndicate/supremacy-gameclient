import { Sequence } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { BT_SearchHiddenLocation } from "./BT_SearchHiddenLocation"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BT_SetFocal } from "./BT_SetFocal"

/**
 * Behavior when AI heard a noise.
 *
 * This behavior will cause AI to move to the noise location. Also, makes an environment query get a possible hidden location based on the noise location and
 * moves to it (@see {@link EQSQueryType.Hidden} and {@link BT_SearchHiddenLocation}).
 *
 * The {@link ParallelBackground} branch node is used to update the current focal point based on different stimulus in background.
 */
 export const BT_InvestigateNoise = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                BTT_SetFocalPoint("noiseLocation"),
                BTT_MoveTo("noiseLocation"),
                BT_SearchHiddenLocation("noiseLocation"),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
            ],
        }),
        BT_SetFocal,
    ],
})
