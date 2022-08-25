import { RUNNING, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Logs the given message to the console.
 *
 * Intended to be used for debugging purpose.
 *
 * @param message The message to log
 */
export const BTT_LogString = (startMessage: (blackboard: AIBlackboard) => string, runMessage?: (blackboard: AIBlackboard) => string) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const message: string = startMessage(blackboard)
            console.log(message)
            return SUCCESS
        },

        run: (blackboard: AIBlackboard) => {
            if (typeof runMessage !== "undefined") {
                const message: string = runMessage(blackboard)
                console.log(message)
            }
            return SUCCESS
        },
    })
