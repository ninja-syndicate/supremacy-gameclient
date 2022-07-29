import { RUNNING, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Logs the given message to the console.
 *
 * Intended to be used for debugging purpose.
 *
 * @param message The message to log
 */
export const BTT_LogString = (startMessage: string, runMessage?: string) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            console.log(startMessage)
            return SUCCESS
        },

        run: (blackboard: AIBlackboard) => {
            if (typeof runMessage !== "undefined") console.log(runMessage)

            return SUCCESS
        },
    })
