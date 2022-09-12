import { AI } from "@root/index"

import { SUCCESS, Task } from "behaviortree"
import { Message } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"

export const BTT_SendMessage = (message: Message) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const success: boolean = AI.SendMessage(message)
            if (!success) {
                console.log("Failed to send a message.")
            }
            return SUCCESS
        },
    })
