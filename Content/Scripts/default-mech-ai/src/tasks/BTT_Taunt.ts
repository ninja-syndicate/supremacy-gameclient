import { Task, SUCCESS, FAILURE, RUNNING } from "behaviortree"
import { AI } from "../index"
import { AIBlackboard } from "../blackboard"
import { IsVector } from "../utils"
import { Ability, Status, MovementResult, Action } from "enums"

/**
 * Move to a location.
 *
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
