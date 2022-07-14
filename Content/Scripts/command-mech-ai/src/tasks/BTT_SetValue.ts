import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * A task that can be used to set/clear the properties of the blackboard.
 *
 * Intended to be used to set the properties of the blackboard while certain branch of the behavior tree is being executed.
 *
 * @param func A setter function that accepts blackboard and modify its properties as you need
 */
export const BTT_SetValue = (func: (blackboard: AIBlackboard) => void) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            func(blackboard)
            return SUCCESS
        },
    })
