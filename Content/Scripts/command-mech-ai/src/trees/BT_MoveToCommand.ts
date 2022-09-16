import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { Sequence } from "behaviortree"
import { Message } from "enums"
import { BTT_SendMessage } from "@tasks/BTT_SendMessage"
import { BT_SprintMoveTo } from "@trees/movement/BT_MovementMode"

export const BT_MoveToCommand = new Sequence({
    nodes: [
        BT_SprintMoveTo("moveCommandLocation", true),
        BTT_SendMessage(Message.MoveCommandComplete),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.isCommanded = false)),
    ],
})
