import { Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { AIBlackboard } from "../blackboard"

/**
 * Investigate noise behavior.
 */
export const BT_InvestigateNoise = new Sequence({
    nodes: [
        BTT_SetFocalPoint("noiseLocation"),
        BTT_MoveTo("noiseLocation"),
        // TODO: Also investigate in possible hidden locations.
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
    ],
})
