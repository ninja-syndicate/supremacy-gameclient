import { Task, SUCCESS, FAILURE, RUNNING } from "behaviortree"
import { AI } from "../index"
import { AIBlackboard } from "../blackboard"
import { IsVector } from "../utils"
import { MovementResult } from "enums"

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
