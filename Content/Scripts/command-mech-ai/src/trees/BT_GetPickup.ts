import { Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_SetFocal } from "@trees/BT_SetFocal"

/**
 * Getting the pickup behavior.
 *
 * When desired pickup location is set, this behavior will cause AI to move to the desired pickup location.
 *
 * The {@link ParallelBackground} (@see {@link ParallelBackground}) node is used to keep updating the focal point to the appropriate location in background
 * while it is moving (e.g. if it gets hit from behind when it has no target, it will update the focal point to eventually look back).
 */
export const BT_GetPickup = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                // Force success to clear the desired pickup location if not navigable.
                new Selector({
                    nodes: [BTT_MoveTo("desiredPickupLocation", true), BTT_Success],
                }),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.desiredPickupLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})
