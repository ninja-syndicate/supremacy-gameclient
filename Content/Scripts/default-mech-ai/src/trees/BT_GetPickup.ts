import { Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_Success } from "../tasks/BTT_Success"
import { BT_SetFocal } from "./BT_SetFocal"

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
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.desiredPickUpLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})
