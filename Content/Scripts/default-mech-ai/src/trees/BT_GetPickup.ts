import { ObserverAborts, Selector, Sequence } from "behaviortree"
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
import { ParallelBackground } from "../branches/ParallelBackground"
import { BT_SetFocal } from "./BT_SetFocal"
import { BTT_Success } from "../tasks/BTT_Success"

/**
 * Picking up behavior.
 */
export const BT_GetPickup = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                // Force success to clear the desired pickup location if not navigable.
                new Selector({
                    nodes: [BTT_MoveTo("desiredPickUpLocation", true), BTT_Success],
                }),
                BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.desiredPickUpLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})
