import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../../blackboard"
import { AI } from "../../index"

/**
 * Stops current movement of AI executed by {@link BTT_MoveTo}.
 *
 * If the AI has already stopped its movement, executing this task will do nothing.
 *
 * @see {@link AI.StopMoveTo} for details.
 */
export const BTT_StopMoveTo = new Task({
    run: (blackboard: AIBlackboard) => {
        AI.StopMoveTo()
        return SUCCESS
    },
})
