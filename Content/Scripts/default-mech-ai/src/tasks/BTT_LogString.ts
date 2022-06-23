import { SUCCESS, Task } from "behaviortree"

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
