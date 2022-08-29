import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_QuerySetArgumentFloat, BTT_QuerySetArgumentString, BTT_QuerySetArgumentVector } from "@tasks/environment/BTT_QuerySetArgument"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"

/**
 * Close Strafing behavior.
 *
 * Makes an environment query to get a much closer strafe location to the target and moves to it (@see {@link EQSQueryType.CloseStrafe}). The close strafe
 * environment query requires {@link EQSArgument.TargetHash} and {@link EQSArgument.TargetLastKnownLocation} to be set before it gets executed by 
 * {@link BTT_RunEQSQuery}.
 *
 * Intended to be used during the combat to be able to strafe much closely to the target.
 */
export const BT_CloseStrafe = new Sequence({
    nodes: [
        BTT_QuerySetArgumentString(EQSQueryType.CloseStrafe, EQSArgument.TargetHash, (blackboard: AIBlackboard) => blackboard.target.hash),
        BTT_QuerySetArgumentVector(
            EQSQueryType.CloseStrafe,
            EQSArgument.TargetLastKnownLocation,
            (blackboard: AIBlackboard) => blackboard.targetLastKnownLocation,
        ),
        BTT_QuerySetArgumentFloat(EQSQueryType.CloseStrafe, EQSArgument.GridSize, (blackboard: AIBlackboard) => 4000),
        BTT_RunEQSQuery(EQSQueryType.CloseStrafe, "closeStrafeLocation"),
        BTT_MoveTo("closeStrafeLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.closeStrafeLocation = undefined)),
    ],
})
