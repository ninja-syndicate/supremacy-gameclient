import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_QuerySetArgumentFloat, BTT_QuerySetArgumentString } from "@tasks/environment/BTT_QuerySetArgument"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BT_MoveByDistanceToTarget } from "@trees/movement/BT_MovementMode"

/**
 * Strafing behavior.
 *
 * Makes an environment query to get the strafe location and moves to it (@see {@link EQSQueryType.Strafe}). The strafe environment query requires
 * {@link EQSArgument.TargetHash} to be set before it gets executed by {@link BTT_RunEQSQuery}.
 *
 * Intended to be used during the combat to be able to strafe while shooting.
 */
export const BT_Strafe = new Sequence({
    nodes: [
        BTT_QuerySetArgumentString(EQSQueryType.Strafe, EQSArgument.TargetHash, (blackboard: AIBlackboard) => blackboard.target.Hash),
        BTT_QuerySetArgumentFloat(EQSQueryType.Strafe, EQSArgument.GridSize, (blackboard: AIBlackboard) => Math.max(20000, blackboard.idealEngagementRange)),
        BTT_QuerySetArgumentFloat(EQSQueryType.Strafe, EQSArgument.MinDistanceToSelf, (blackboard: AIBlackboard) => 3000),
        BTT_QuerySetArgumentFloat(EQSQueryType.Strafe, EQSArgument.MinDistanceToTarget, (blackboard: AIBlackboard) => 0),
        BTT_QuerySetArgumentFloat(EQSQueryType.Strafe, EQSArgument.MaxDistanceToTarget, (blackboard: AIBlackboard) => blackboard.idealEngagementRange),
        BTT_RunEQSQuery(EQSQueryType.Strafe, "strafeLocation"),
        BT_MoveByDistanceToTarget("strafeLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.strafeLocation = undefined)),
    ],
})
