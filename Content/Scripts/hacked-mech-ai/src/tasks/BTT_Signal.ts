import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { Signal, Status } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"

// NOTE: this is not currently implemented yet so don't use it.
// TODO: do implementation for signal
/**
 * Sends the specified signal.
 * 
 * @param signal 
 */
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
