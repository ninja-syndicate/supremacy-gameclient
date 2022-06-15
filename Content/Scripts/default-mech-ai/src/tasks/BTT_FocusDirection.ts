import {Task, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsVector, IsWarMachine} from "../utils"
import {add, multiply} from "../helper"

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_FocusDirection = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const direction = blackboard[blackboardKey];
        if (!direction || !IsVector(direction))
            return FAILURE;

        // TODO: Use vector math library.
        const focalPoint = add(blackboard.input.self.location, multiply(direction, 1000));
        AI.SetFocalPointByLocation(focalPoint);
        return SUCCESS;
    }
});