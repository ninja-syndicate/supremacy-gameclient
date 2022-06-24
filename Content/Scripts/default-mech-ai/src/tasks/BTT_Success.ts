import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"

/**
 * A task that always returns SUCCESS.
 *
 * Useful if you want the wrapping Selector to succeed when all other tasks fail.
 */
export const BTT_Success = new Task({
    run: (blackboard: AIBlackboard) => {
        return SUCCESS
    },
})
