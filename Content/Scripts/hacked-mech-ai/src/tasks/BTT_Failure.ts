import { FAILURE, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * A task that always returns FAILURE.
 *
 * Useful if you want a wrapping Selector/Sequence to fail after executing other behaviors/tasks.
 */
export const BTT_Failure = new Task({
    run: (blackboard: AIBlackboard) => {
        return FAILURE
    },
})
