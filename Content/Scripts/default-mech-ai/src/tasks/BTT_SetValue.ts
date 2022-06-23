import { SUCCESS, Task } from 'behaviortree';
import { AIBlackboard } from "../blackboard";

export const BTT_SetValue = (func: (blackboard: AIBlackboard) => void) => new Task({
    run: (blackboard: AIBlackboard) => {
        func(blackboard);
        return SUCCESS;
    }
});