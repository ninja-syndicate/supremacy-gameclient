import { ObserverAborts, Parallel, ParallelSelector, Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString } from "../tasks/BTT_EQSSetArgument"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LogString } from "../tasks/BTT_LogString"

/**
 *
 */
export const BT_Strafe = new Sequence({
    nodes: [
        BTT_EQSSetArgumentString(EQSQueryType.Strafe, EQSArgument.TargetHash, (blackboard: AIBlackboard) => blackboard.target.hash),
        BTT_RunEQSQuery(EQSQueryType.Strafe, "strafeLocation"),
        BTT_MoveTo("strafeLocation"),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.strafeLocation = undefined)),
    ],
})
