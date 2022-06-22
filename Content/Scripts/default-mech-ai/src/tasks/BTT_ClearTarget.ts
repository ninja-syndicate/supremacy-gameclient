import { Task, SUCCESS } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { clearBlackboardTarget } from "../mech"

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_ClearTarget = new Task({
    run: (blackboard: AIBlackboard) => {
        clearBlackboardTarget()
        return SUCCESS
    },
})
