import { Selector, Sequence } from "behaviortree"
import { BT_GetCover } from "./BT_GetCover"
// import { BT_LookAround } from "./BT_LookAround"
import { AIBlackboard } from "../blackboard"
import { ParallelBackground } from "../branches/ParallelBackground"
import { IsSet } from "../decorators/IsSet"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BT_LookAround } from "./BT_LookAround"
import { BT_SetFocal } from "./BT_SetFocal"
import { BTT_SetValue } from "../tasks/BTT_SetValue"

export const BT_Camp = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                new Sequence({
                    nodes: [
                        new Selector({
                            nodes: [IsSet(BT_GetCover, "coverLocation", false), IsSet(BTT_MoveTo("coverLocation"), "coverLocation")],
                        }),
                        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)),
                    ],
                }),
                BT_SetFocal,
            ],
        }),
        BT_LookAround,
    ],
})
