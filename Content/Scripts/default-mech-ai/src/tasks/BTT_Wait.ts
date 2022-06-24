import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"

import { Action, Status } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Makes the AI wait for the specified number of seconds.
 *
 * @see {@link AI.Wait} for details.
 *
 * @param seconds The number of seconds AI must wait.
 */
export const BTT_Wait = (seconds: number) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const success: boolean = AI.Wait(seconds)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            const status: Status = AI.QueryStatus(Action.Wait)
            switch (status) {
                case Status.Running:
                    return RUNNING
                case Status.Failed:
                    return FAILURE
                case Status.Finished:
                    return SUCCESS
                default:
                    return FAILURE
            }
        },
    })