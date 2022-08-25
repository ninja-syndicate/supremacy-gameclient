import { RUNNING, Task } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * A task that always returns RUNNING.
 *
 * Useful if you want a particular branch to continue executing while waiting for some decorator observer abort condition to be met.
 */
export const BTT_Running = new Task({
    run: (blackboard: AIBlackboard) => {
        return RUNNING
    },
})
