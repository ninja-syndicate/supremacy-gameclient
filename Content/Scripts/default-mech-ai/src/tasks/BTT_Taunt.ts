import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { Action, Status } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Makes AI taunt.
 *
 * @see {@link AI.Taunt} for details.
 */
export const BTT_Taunt = new Task({
    start: (blackboard: AIBlackboard) => {
        const success: boolean = AI.Taunt()
        return success ? SUCCESS : FAILURE
    },

    run: (blackboard: AIBlackboard) => {
        const status: Status = AI.QueryStatus(Action.Taunt)
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
