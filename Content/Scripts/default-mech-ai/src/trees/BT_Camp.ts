import { Parallel, Selector, Sequence } from "behaviortree"
import { BT_GetCover } from "./BT_GetCover"
import { BT_LookAround } from "./BT_LookAround"
import { BTT_Wait } from "../tasks/BTT_Wait"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { AIBlackboard } from "../blackboard"
import { IsSet } from "../decorators/IsSet"
import { Predicate } from "../decorators/Predicate"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"

export const BT_Camp = new Sequence({
    nodes: [
        new Selector({
            nodes: [IsSet(BT_GetCover, "coverLocation", false), BTT_MoveTo("coverLocation")],
        }),
        new Sequence({
            nodes: [BT_LookAround, BTT_Wait(3), BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined))],
        }),
    ],
})
