import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { Signal, Status } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

export const BTT_Signal = (signal: Signal) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            AI.SendSignal(signal)
            return SUCCESS
        },
        run: (blackboard: AIBlackboard) => {
            const status = AI.QueryStatus(signal)

            switch (status) {
                case Status.Running:
                    return RUNNING
                case Status.Failed:
                    return FAILURE
                case Status.Finished:
                    return SUCCESS
                default:
                    return FAILURE
            }
        },
    })
