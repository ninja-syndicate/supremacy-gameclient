import {Task, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsIntVector} from "../utils"

/**
 * Move to a location.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 * @param blackboardKey IntVector
 */
export const BTT_MoveTo = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const value = blackboard[blackboardKey]
        if (!value || !IsIntVector(value))
            return FAILURE
        AI.MoveToVector(value)
        // TODO: Figure out a way to make this task not succeed until the move is complete (need to do something on unreal side)
        return SUCCESS
    }
})

