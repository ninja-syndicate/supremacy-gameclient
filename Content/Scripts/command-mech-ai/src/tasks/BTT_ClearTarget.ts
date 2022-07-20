import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { clearBlackboardTarget } from "../mech"

// NOTE: This task may be removed in the future.
/**
 * Clears the target information stored in the blackboard.
 */
export const BTT_ClearTarget = new Task({
    run: (blackboard: AIBlackboard) => {
        clearBlackboardTarget()
        return SUCCESS
    },
})
