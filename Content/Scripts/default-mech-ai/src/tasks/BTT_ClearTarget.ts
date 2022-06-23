import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { clearBlackboardTarget } from "../mech"

export const BTT_ClearTarget = new Task({
    run: (blackboard: AIBlackboard) => {
        clearBlackboardTarget()
        return SUCCESS
    },
})
