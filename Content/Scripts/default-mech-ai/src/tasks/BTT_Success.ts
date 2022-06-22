import { Task, SUCCESS, FAILURE } from "behaviortree"
import { AI } from "../index"
import { AIBlackboard } from "../blackboard"
import { IsVector, IsWarMachine } from "../utils"

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_Success = new Task({
    run: (blackboard: AIBlackboard) => {
        return SUCCESS
    },
})
