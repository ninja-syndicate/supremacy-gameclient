import { SUCCESS, Task } from "behaviortree"
import { AIBlackboard } from "../blackboard"

/**
 * A task that can be used to set the properties of the blackboard using {@link func} function.
 *
 * You may want to set the properties of the blackboard when certain conditions are met while the behavior tree is being executed. You can use this task to achieve that.
 *
 * @param func A setter function that accepts blackboard and modify its properties as you need.
 */
export const BTT_SetValue = (func: (blackboard: AIBlackboard) => void) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            func(blackboard)
            return SUCCESS
        },
    })
