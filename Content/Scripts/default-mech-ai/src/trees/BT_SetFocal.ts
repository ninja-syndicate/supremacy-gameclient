import { ObserverAborts, Selector } from "behaviortree"
import { IsSet } from "../decorators/IsSet"
import { BTT_Success } from "../tasks/BTT_Success"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 * Behavior for setting the focal point of the AI.
 *
 * The focal point 
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
