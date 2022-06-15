import { Task, SUCCESS } from "behaviortree"
import { AIBlackboard } from "../blackboard"

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_ClearValue = (clearFunc: (blackboard: AIBlackboard) => void) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            clearFunc(blackboard)
            return SUCCESS
        },
    })
