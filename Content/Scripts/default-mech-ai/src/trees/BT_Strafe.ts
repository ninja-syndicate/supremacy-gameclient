import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { AIBlackboard } from "../blackboard"
import { BTT_EQSSetArgumentString } from "../tasks/environment/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"

/**
 * AI strafing behavior.
 */
export const BT_Strafe = new Sequence({
    nodes: [
        BTT_EQSSetArgumentString(EQSQueryType.Strafe, EQSArgument.TargetHash, (blackboard: AIBlackboard) => blackboard.target.hash),
        BTT_RunEQSQuery(EQSQueryType.Strafe, "strafeLocation"),
        BTT_MoveTo("strafeLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.strafeLocation = undefined)),
    ],
})
