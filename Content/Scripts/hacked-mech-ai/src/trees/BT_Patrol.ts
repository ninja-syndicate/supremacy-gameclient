import { Sequence } from "behaviortree"
import { EQSQueryType } from "enums"
import { AIBlackboard } from "../blackboard"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Patrol behavior.
 *
 * Makes an environment query to get the patrol location and moves to it (@see {@link EQSQueryType.Patrol}).
 */
export const BT_Patrol = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
        BTT_SetFocalPoint("patrolLocation"),
        BTT_MoveTo("patrolLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.patrolLocation = undefined)),
    ],
})
