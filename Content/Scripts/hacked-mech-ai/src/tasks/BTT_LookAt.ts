import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { Action, Status } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"
import { IsVector } from "../utils"

/**
 * Makes AI look at a location.
 *
 * This task is different from {@link BTT_SetFocalPoint} as this {@link AI.LookAt} action waits for AI to actually face in the location you specified. Setting
 * the focal point by {@link BTT_SetFocalPoint} or making a move to request by {@link BTT_MoveTo} will cancel this action (@see {@link AI.LookAt}).
 *
 * @param {Vector} blackboardKey the location to look at
 */
export const BTT_LookAt = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            // Check if the blackboard key is a Vector.
            const location = blackboard[blackboardKey]
            if (!location || !IsVector(location)) return

            const success: boolean = AI.LookAt(location)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            const status = AI.QueryStatus(Action.LookAt)
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
