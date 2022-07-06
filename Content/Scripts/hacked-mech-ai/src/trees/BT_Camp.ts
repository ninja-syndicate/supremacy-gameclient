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
 * If AI has a cover location, it will move to it. This is useful in the case where the task to move to the cover location gets aborted/failed before
 * completion. So it doesn't need to request a new cover location which may be further than the current cover location. Otherwise, it will move to a new cover
 * location.
 *
 * The {@link ParallelBackground} (@see {@link ParallelBackground}) node is used to keep updating the focal point to the appropriate location in background
 * while it is moving (e.g. if it gets hit from behind when it has no target, it will update the focal point to eventually look back).
 *
 * The {@link BT_LookAround} at the end makes AI look around after getting to the cover location to see if there are any enemies around. You may remove this if
 * you don't like this behavior.
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
