import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../../blackboard"

/**
 * Logs the given message to the console.
 *
 * Intended to be used for debugging purpose.
 *
 * @param message The message to log
 */
export const BTT_LogString = (message: string) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            console.log(message)
            return SUCCESS
        },
    })
