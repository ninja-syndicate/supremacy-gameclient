import {Task, RUNNING, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsVector, IsWarMachine} from "../utils"
import { Ability, Status } from 'enums';

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_LookAt = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const location = blackboard[blackboardKey];
        if (!location || !IsVector(location))
            return FAILURE;
        
        AI.LookAt(location);
        const status = AI.QueryStatus(Ability.SpecialAttack);
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