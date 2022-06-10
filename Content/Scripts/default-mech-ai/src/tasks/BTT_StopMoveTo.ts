import {Task, SUCCESS, FAILURE, RUNNING} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard} from "../blackboard"
import {IsVector} from "../utils"
import {MovementResult} from "enums"

/**
 * Move to a location.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 * @param blackboardKey IntVector
 * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
 */
export const BTT_StopMoveTo = () => new Task({
    run: () => {
        AI.StopMoveTo();
        return SUCCESS;
    }
});