import { SUCCESS, Task } from "behaviortree"

/**
 * Logs the given message to the console.
 *
 * Intended to be used for debugging purpose.
 *
 * @param message The message to log
 */
export const BTT_LogString = (message: string) =>
    new Task({
        run: () => {
            console.log(message)
            return SUCCESS
        },
    })