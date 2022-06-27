import { ObserverAborts, Selector } from "behaviortree"
import { IsSet } from "../decorators/IsSet"
import { BTT_Success } from "../tasks/BTT_Success"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Behavior for setting the focal point of AI.
 *
 * Sets the focal point of AI to the most desirable target/location.
 * Currently, the priority for setting the focal point is defined as follows:
 *
 *  - {@link AIBlackboard.target} if AI can see the current target
 *  - {@link AIblackboard.damageStimulusFocalPoint} if AI received the damage
 *  - {@link AIBlackboard.targetPredictedLocation} if AI has the target's predicted location
 *  - {@link AIBlackboard.targetLastKnownLocation} if AI has the target's last known location
 *
 * You may want to wrap around this behavior with a {@link ForceSuccess} decorator if used with a {@link ParalellBackground} branch node.
 */
export const BT_SetFocal = new Selector({
    nodes: [
        IsSet(BTT_SetFocalPoint("target"), "canSeeTarget", true, ObserverAborts.LowerPriority),
        // TODO: Need to figure out better approach for focusing to the damage.
        IsSet(BTT_SetFocalPoint("damageStimulusFocalPoint"), "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BTT_SetFocalPoint("targetPredictedLocation"), "targetPredictedLocation", true, ObserverAborts.LowerPriority),
        IsSet(BTT_SetFocalPoint("targetLastKnownLocation"), "targetLastKnownLocation", true, ObserverAborts.LowerPriority),
        // TODO: This success can be removed if ForceSuccess decorator worked.
        BTT_Success,
    ],
})
