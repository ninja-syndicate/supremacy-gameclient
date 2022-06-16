import { Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { AI } from ".."
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LogString } from "../tasks/BTT_LogString"
import { IsSet } from "../decorators/IsSet"
import { BTT_SetValue } from "../tasks/BTT_SetValue"

/**
 * Picking up behavior.
 */
export const BT_GetPickup = new Sequence({
    nodes: [
        ForceSuccess(Predicate(BTT_SetFocalPoint("desiredPickUpLocation"), (blackboard: AIBlackboard) => !AI.IsFocalPointSet())),
        BTT_MoveTo("desiredPickUpLocation"),
    ],
})
