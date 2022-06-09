import {Task, SUCCESS, FAILURE, RUNNING} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsVector} from "../utils"
import {Ability, Status, MovementResult} from "enums"

/**
 * Move to a location.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 * @param blackboardKey IntVector
 * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
 */
export const BTT_Taunt = () => new Task({
    run: () => {
        AI.Taunt();
    
        const status: Status = AI.QueryStatus(Ability.Taunt);
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
})

