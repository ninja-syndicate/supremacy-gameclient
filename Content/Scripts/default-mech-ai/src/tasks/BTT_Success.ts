import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"

export const BTT_Success = new Task({
    run: (blackboard: AIBlackboard) => {
        return SUCCESS
    },
})
