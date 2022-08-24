import { AIBlackboard } from "@blackboards/blackboard"
import { SUCCESS, Task } from "behaviortree"
import { AI } from "@root/index"
import { ENABLE_DEBUGGING } from "@root/aiconfig"

/**
 * Clears the focal point of AI set by {@link BTT_SetFocalPoint}.
 */
export const BTT_ClearFocalPoint = new Task({
    start: (blackboard: AIBlackboard) => {
        if (ENABLE_DEBUGGING) {
            console.log("BTT_ClearFocalPoint: Focus Cleared.")
        }
        return SUCCESS
    },
    run: (blackboard: AIBlackboard) => {
        AI.ClearFocus()
        return SUCCESS
    },
})
