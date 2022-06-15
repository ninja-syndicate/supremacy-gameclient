import { Task, SUCCESS, FAILURE } from "behaviortree"
import { AI } from "../../index"
import { AIBlackboard } from "../../blackboard"
import { IsVector, IsWarMachine } from "../../utils"

/**
 * Sets the focal point of AI.
 *
 * @param blackboardKey WarMachine or Vector
 */
export const BTT_SetFocalPoint = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            return SUCCESS
        },

        run: (blackboard: AIBlackboard) => {
            const value = blackboard[blackboardKey]
            if (!value) return FAILURE

            if (IsWarMachine(value)) {
                AI.SetFocalPointByHash(value.hash)
                return SUCCESS
            } else if (IsVector(value)) {
                AI.SetFocalPointByLocation(value)
                return SUCCESS
            }
            return FAILURE
        },
    })
