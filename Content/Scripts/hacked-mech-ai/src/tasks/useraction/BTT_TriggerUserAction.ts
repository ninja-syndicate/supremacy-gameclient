import { FAILURE, SUCCESS, Task } from "behaviortree"
import { UserAction } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"

export const BTT_TriggerUserAction = (userAction: UserAction) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const success: boolean = AI.TriggerUserAction(userAction)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            return SUCCESS
        },
    })
