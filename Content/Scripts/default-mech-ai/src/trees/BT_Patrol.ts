import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BTT_QuerySetArgumentFloat, BTT_QuerySetArgumentVector } from "@tasks/environment/BTT_QuerySetArgument"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { BT_DefaultMoveTo } from "@trees/movement/BT_MovementMode"
import { BTT_LogString } from "@root/tasks/debug/BTT_LogString"

/**
 * Patrol behavior.
 *
 * Makes an environment query to get the patrol location and moves to it (@see {@link EQSQueryType.Patrol}).
 * The {@link ParallelBackground} branch node is used to update the current focal point based on different stimulus in background.
 */
export const BT_Patrol = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                BTT_QuerySetArgumentVector(EQSQueryType.Patrol, EQSArgument.Origin, (blackboard: AIBlackboard) => blackboard.input.Self.Location),
                BTT_QuerySetArgumentFloat(EQSQueryType.Patrol, EQSArgument.GridSize, (blackboard: AIBlackboard) => 30000),
                BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
                BTT_SetFocalPoint("patrolLocation"),
                BT_DefaultMoveTo("patrolLocation"),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.patrolLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})