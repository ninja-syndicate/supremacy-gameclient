import { Sequence } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { BTT_ClearTarget } from "@tasks/BTT_ClearTarget"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { BT_SearchHiddenLocation } from "@trees/BT_SearchHiddenLocation"

/**
 * Behavior for searching the target.
 *
 * Makes AI first move to the target's last known location and the possible hidden location based on the target's predicted location. The 
 * {@link ParallelBackground} branch node is used to run {@link BT_SetFocal} as a background task to update the focal point to the appropriate target/location
 * while it is moving.
 *
 * Clears the current target when AI finishes searching for both locations and is not aborted by any higher priority behavior trees with
 * {@link ObserverAborts.LowerPriority} or {@link ObserverAborts.Both}.
 *
 * This behavior requires at least {@link AIBlackboard.targetLastKnownLocation} to be set to run. Otherwise, it will fail.
 */
export const BT_SearchTarget = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                new Sequence({
                    nodes: [
                        IsSet(BTT_MoveTo("targetLastKnownLocation"), "targetLastKnownLocation"),
                        IsSet(BT_SearchHiddenLocation("targetPredictedLocation"), "targetPredictedLocation"),
                    ],
                }),
                BT_SetFocal,
            ],
        }),
        BTT_ClearTarget,
    ],
})
