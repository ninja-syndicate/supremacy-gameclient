import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { Predicate } from "@decorators/Predicate"
import { Predicate_IsLocationInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"

/**
 * Getting the pickup behavior.
 *
 * When desired pickup location is set, this behavior will cause AI to move to the desired pickup location if it is inside the main battle zone. You may modify
 * this behavior to allow the AI to pickup outside the main battle zone using your own heuristics.
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
                    nodes: [
                        Predicate(
                            BTT_MoveTo("desiredPickupLocation", true),
                            Predicate_IsLocationInsideBattleZone("desiredPickupLocation"),
                            true,
                            ObserverAborts.Self,
                        ),
                        BTT_Success,
                    ],
                }),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.desiredPickupLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})
