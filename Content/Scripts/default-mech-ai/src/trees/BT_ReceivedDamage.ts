import { Sequence } from "behaviortree"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_StopMoveTo } from "../tasks/BTT_StopMoveTo"
import { AIBlackboard } from "../blackboard"

/**
 * Behavior when AI receives damage.
 */
export const BT_ReceivedDamage = new Sequence({
    nodes: [
        BTT_StopMoveTo(),
        BTT_LookAt("damageStimulusFocalPoint"),
        // TODO: Investigate in the direction of damage stimulus and possible hidden locations.
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.damageStimulusFocalPoint = undefined)),
    ],
})
