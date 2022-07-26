import { Sequence } from "behaviortree"
import { EQSQueryType } from "enums"
import { AIBlackboard } from "../blackboard"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { BTT_QuerySetArgumentFloat, BTT_QuerySetArgumentVector } from "../tasks/environment/BTT_QuerySetArgument"
import { EQSArgument } from "enums"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BT_SetFocal } from "./BT_SetFocal"

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
                BTT_QuerySetArgumentVector(EQSQueryType.Patrol, EQSArgument.Origin, (blackboard: AIBlackboard) => blackboard.input.self.location),
                BTT_QuerySetArgumentFloat(EQSQueryType.Patrol, EQSArgument.GridSize, (blackboard: AIBlackboard) => 15000),
                BTT_QuerySetArgumentFloat(EQSQueryType.Patrol, EQSArgument.SpaceBetween, (blackboard: AIBlackboard) => 1000),
                BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
                BTT_SetFocalPoint("patrolLocation"),
                BTT_MoveTo("patrolLocation"),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.patrolLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})