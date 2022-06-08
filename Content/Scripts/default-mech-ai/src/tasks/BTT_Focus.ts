import {Task, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsIntVector, IsWarMachine} from "../utils"

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_Focus = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const value = blackboard[blackboardKey]
        if (!value)
            return FAILURE
        if (IsWarMachine(value)) {
            AI.FocusHash(value.hash)
            return SUCCESS
        } else if (IsIntVector(value)) {
            AI.FocusLocation(value)
            return SUCCESS
        }
        return FAILURE
    }
})

/** Stop looking at WarMachine/IntVector from {@link BTT_Focus}. */
export const BTT_StopFocus = new Task({
    run: () => {
        AI.ClearFocus()
        return SUCCESS
    }
})
