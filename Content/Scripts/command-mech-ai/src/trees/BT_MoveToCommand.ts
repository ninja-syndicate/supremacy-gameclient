import { AIBlackboard } from "@blackboards/blackboard"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { Sequence } from "behaviortree"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { Message } from "enums"
import { BTT_SendMessage } from "@root/tasks/BTT_SendMessage"

export const BT_MoveToCommand = new Sequence({
    nodes: [
        BTT_MoveTo("moveCommandLocation", true),
        BTT_SendMessage(Message.MoveCommandComplete),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.isCommanded = false)),
    ],
})
