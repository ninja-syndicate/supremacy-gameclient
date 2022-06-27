import { Selector, Sequence } from "behaviortree"
import { BT_GetCover } from "./BT_GetCover"
import { AIBlackboard } from "../blackboard"
import { ParallelBackground } from "../branches/ParallelBackground"
import { IsSet } from "../decorators/IsSet"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BT_LookAround } from "./BT_LookAround"
import { BT_SetFocal } from "./BT_SetFocal"
import { BTT_SetValue } from "../tasks/BTT_SetValue"

/**
 * Camping behavior.
 *
 * Makes the AI move to the cover location if it.
 *
 * If it already has a cover location, it will move to it. This is useful in case the task to move to the cover location gets cancelled. So it doesn't need to
 * request a new cover location which may be further than the current cover location.
 *
 * At the end, 
 */
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
