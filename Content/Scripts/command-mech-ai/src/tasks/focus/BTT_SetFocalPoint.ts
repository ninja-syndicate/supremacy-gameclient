import { FAILURE, SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"
import { IsVector, IsWarMachine } from "../../utils"

/**
 * Sets the focal point of AI to the specified war machine/location.
 *
 * Note that this task is different from {@link BTT_LookAt} as this task will set the focal point and return SUCCESS immediately. Since AI takes some time to
 * rotate to face the location, it does not guarantee that AI will be facing in the specified location when this task finishes.
 *
 * @param {WarMachine | Vector} blackboardKey the location to set the focal point to
 */
export const BTT_SetFocalPoint = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            // Check if the blackboard key is valid.
            const value = blackboard[blackboardKey]
            if (!value) return FAILURE

            // Make an appropriate focal point call depending on the blackboard key type.
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
