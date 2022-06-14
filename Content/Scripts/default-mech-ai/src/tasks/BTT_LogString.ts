import { Task, SUCCESS, FAILURE } from "behaviortree"
import { AI } from "../index"

/**
 * Logs the string.
 */
export const BTT_LogString = (message: string) =>
    new Task({
        run: () => {
            console.log(message)
            return SUCCESS
        },
    })
