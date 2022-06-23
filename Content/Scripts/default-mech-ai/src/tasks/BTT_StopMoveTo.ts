import { SUCCESS, Task } from "behaviortree"
import { AI } from "../index"

/**
 * Stops movement.
 *
 * If the AI has already stopped its movement, executing this task will not do
 * anything.
 */
export const BTT_StopMoveTo = () =>
    new Task({
        run: () => {
            AI.StopMoveTo()
            return SUCCESS
        },
    })
