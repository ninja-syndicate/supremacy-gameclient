import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { Predicate } from "@decorators/Predicate"
import { Predicate_IsLocationInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { BT_SprintMoveTo } from "@trees/movement/BT_MovementMode"

/**
 * Getting the pickup behavior.
 *
 * When desired pickup location is set, this behavior will cause AI to move to the desired pickup location if it is inside the main battle zone. You may modify
 * this behavior to allow the AI to pickup outside the main battle zone using your own heuristics.
 *
 * Note that this behavior will make your AI to sprint if capable.
 *
 * The {@link ParallelBackground} (@see {@link ParallelBackground}) node is used to keep updating the focal point to the appropriate location in background
 * while it is moving (e.g. if it gets hit from behind when it has no target, it may update the focal point to eventually look back).
 */
export const BT_GetPickup = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                new Selector({
                    nodes: [
                        Predicate(
                            // TODO: Add a condition to check whether it can sprint and make a behavior for it.
                            BT_SprintMoveTo("desiredPickupLocation", true),
                            Predicate_IsLocationInsideBattleZone("desiredPickupLocation"),
                            true,
                            ObserverAborts.Self,
                        ),
                    ],
                }),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.desiredPickupLocation = undefined)),
            ],
        }),
        BT_SetFocal,
    ],
})
