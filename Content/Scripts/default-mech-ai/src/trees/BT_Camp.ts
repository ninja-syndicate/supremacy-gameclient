import { Parallel, Selector, Sequence } from "behaviortree"
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

export const BT_Camp = new Sequence({
    nodes: [
        new Selector({
            nodes: [IsSet(BT_GetCover, "coverLocation", false), IsSet(BTT_MoveTo("coverLocation"), "coverLocation")],
        }),
        new Sequence({
            nodes: [BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)), BT_LookAround],
        }),
    ],
})
