import {Task, RUNNING, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsVector, IsWarMachine} from "../utils"
import { Ability, Action, Status } from 'enums';

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_LookAt = (blackboardKey: keyof AIBlackboard) => new Task({
    start: (blackboard: AIBlackboard) => {
        const location = blackboard[blackboardKey];
        if (!location || !IsVector(location))
            return;

        AI.LookAt(location);
        return SUCCESS;
    },
    run: (blackboard: AIBlackboard) => {
        const status = AI.QueryStatus(Action.LookAt);
        switch (status) {
            case Status.Running:
                return RUNNING;
            case Status.Failed:
                return FAILURE;
            case Status.Finished:
                return SUCCESS;
            default:
                return FAILURE;
        }
    }
});