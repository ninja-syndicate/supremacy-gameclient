import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Stops current movement being executed by the AI.
 *
 * If the AI has already stopped its movement, executing this task will not do
 * anything.
 *
 * @see {@link AI.StopMoveTo} for details.
 */
export const BTT_StopMoveTo = new Task({
    run: (blackboard: AIBlackboard) => {
        AI.StopMoveTo()
        return SUCCESS
    },
})
