import { Sequence } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { add, multiply } from "../helper"
import { BTT_LookAt } from "../tasks/BTT_LookAt"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_StopMoveTo } from "../tasks/movement/BTT_StopMoveTo"
import { BT_SearchHiddenLocation } from "./BT_SearchHiddenLocation"

/**
 * Behavior when AI receives a damage.
 *
 * Makes the AI stop its current movement, look at its damage direction and search for the possible hidden location that damage instigator may be at.
 * Currently, not intended to be used when AI is in combat state as {@link BTT_LookAt} takes some time to rotate AI to look at the desired location.
 */
export const BT_ReceivedDamage = new Sequence({
    nodes: [
        BTT_StopMoveTo,
        BTT_LookAt("damageStimulusFocalPoint"),
        BTT_SetValue((blackboard: AIBlackboard) => (delete blackboard.damageStimulusFocalPoint)),
        BTT_SetValue(
            (blackboard: AIBlackboard) =>
                (blackboard.damageHiddenLocation = add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 10000))),
        ),
        BT_SearchHiddenLocation("damageHiddenLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (delete blackboard.damageHiddenLocation)),
    ],
})
