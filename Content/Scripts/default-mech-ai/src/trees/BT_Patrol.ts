import { Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { EQSQueryType } from "enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { IsSet } from "../decorators/IsSet"
import { AIBlackboard } from "../blackboard"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"

/**
 * Patrol behavior.
 */
export const BT_Patrol = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
        BTT_SetFocalPoint("patrolLocation"),
        BTT_MoveTo("patrolLocation"),
        IsSet(
            new Sequence({
                nodes: [
                    BTT_SetFocalPoint("targetLastKnownLocation"),
                    BTT_MoveTo("targetLastKnownLocation"),
                    BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.targetLastKnownLocation = undefined)),
                ],
            }),
            "targetLastKnownLocation",
        ),
    ],
})
