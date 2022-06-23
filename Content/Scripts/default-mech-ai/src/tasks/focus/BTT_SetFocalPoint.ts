import { FAILURE, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../../blackboard"
import { AI } from "../../index"
import { IsVector, IsWarMachine } from "../../utils"

/**
 * Sets the focal point of AI.
 *
 * @param blackboardKey WarMachine or Vector
 */
export const BTT_SetFocalPoint = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const value = blackboard[blackboardKey]
            if (!value) return FAILURE

            if (IsWarMachine(value)) {
                const success = AI.SetFocalPointByHash(value.hash)
                return success ? SUCCESS : FAILURE
            } else if (IsVector(value)) {
                const success = AI.SetFocalPointByLocation(value)
                return success ? SUCCESS : FAILURE
            }
            console.log("BTT_SetFocalPoint: Invalid focal point type.")
            return FAILURE
        },

        run: (blackboard: AIBlackboard) => {
            return SUCCESS
        },
    })
