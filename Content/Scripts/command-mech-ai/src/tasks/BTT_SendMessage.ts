import { AI } from "@root/index"

import { SUCCESS, Task } from "behaviortree"
import { Message } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"

export const BTT_SendMessage = (message: Message) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            AI.SendMessage(message)
            return SUCCESS
        },
    })
