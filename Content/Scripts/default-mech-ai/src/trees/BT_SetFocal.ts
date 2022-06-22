import { ObserverAborts, Parallel, Selector, Sequence } from "behaviortree"
import { BT_GetCover } from "./BT_GetCover"
// import { BT_LookAround } from "./BT_LookAround"
import { BTT_Wait } from "../tasks/BTT_Wait"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { AIBlackboard } from "../blackboard"
import { IsSet } from "../decorators/IsSet"
import { Predicate } from "../decorators/Predicate"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_LogString } from "../tasks/BTT_LogString"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BT_LookAround } from "./BT_LookAround"
import { BTT_Success } from "../tasks/BTT_Success"

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
