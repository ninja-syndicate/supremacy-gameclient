import { ObserverAborts, Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ForceSuccess } from "@decorators/ForceSuccess"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_SearchHiddenLocation } from "@trees/BT_SearchHiddenLocation"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { Predicate } from "@decorators/Predicate"
import { Predicate_IsLocationInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"

/**
 * Behavior when AI heard a noise.
 *
 * This behavior will cause AI to move to the noise location if it is inside the main battle zone. Also, makes an environment query get a possible hidden
 * location based on the noise location and moves to it (@see {@link EQSQueryType.Hidden} and {@link BT_SearchHiddenLocation}).
 *
 * The {@link ParallelBackground} branch node is used to update the current focal point based on different stimulus in background.
 */
export const BT_InvestigateNoise = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                // BTT_SetFocalPoint("noiseLocation"),
                Predicate(BTT_MoveTo("noiseLocation"), Predicate_IsLocationInsideBattleZone("noiseLocation"), true, ObserverAborts.Self),
                BT_SearchHiddenLocation("noiseLocation"),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.noiseLocation = undefined)),
                BTT_SetValue((blackboard: AIBlackboard) => (blackboard.heardNoise = false)),
            ],
        }),
        BT_SetFocal,
    ],
})
