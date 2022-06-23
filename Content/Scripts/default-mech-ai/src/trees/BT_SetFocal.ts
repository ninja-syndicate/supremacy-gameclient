import { ObserverAborts, Selector } from "behaviortree"
// import { BT_LookAround } from "./BT_LookAround"
import { IsSet } from "../decorators/IsSet"
import { BTT_Success } from "../tasks/BTT_Success"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

export const BT_SetFocal = new Selector({
    nodes: [
        IsSet(BTT_SetFocalPoint("target"), "canSeeTarget", true, ObserverAborts.LowerPriority),
        // TODO: Need to figure out better approach for focusing to the damage.
        IsSet(BTT_SetFocalPoint("damageStimulusFocalPoint"), "damageStimulusFocalPoint", true, ObserverAborts.LowerPriority),
        IsSet(BTT_SetFocalPoint("targetPredictedLocation"), "targetPredictedLocation", true, ObserverAborts.LowerPriority),
        IsSet(BTT_SetFocalPoint("targetLastKnownLocation"), "targetLastKnownLocation", true, ObserverAborts.LowerPriority),
        BTT_Success,
    ],
})
