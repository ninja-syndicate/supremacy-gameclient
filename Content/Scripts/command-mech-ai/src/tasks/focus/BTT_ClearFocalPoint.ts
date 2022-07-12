import { AIBlackboard } from "@blackboards/blackboard"
import { SUCCESS, Task } from "behaviortree"
import { AI } from "@root/index"

/**
 * Clears the focal point of AI set by {@link BTT_SetFocalPoint}.
 */
export const BTT_ClearFocalPoint = new Task({
    run: (blackboard: AIBlackboard) => {
        AI.ClearFocus()
        return SUCCESS
    },
})
