import { Parallel, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString, BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { AI } from ".."
import { ForceSuccess } from "../decorators/ForceSuccess"

export const BT_LookAround = new Sequence({ nodes: [] })

/**
 *
 */
/*
export const BT_LookAround = new Sequence({
    nodes: [BTT_LookAt(""), BTT_Wait(), BTT_LookAt(""), BTT_Wait(), BTT_LookAt(""), BTT_Wait()],
})
*/
