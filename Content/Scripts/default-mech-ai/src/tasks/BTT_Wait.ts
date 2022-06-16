import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"

import { AI } from "../index"
import { Action, Status, WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"

/**
 * Triggers the specified weapon by tag.
 */
export const BTT_Wait = (seconds: number) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const success: boolean = AI.Wait(seconds)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            const status: Status = AI.QueryStatus(Action.Wait)
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
