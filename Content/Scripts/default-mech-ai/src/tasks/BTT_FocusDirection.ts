import { FAILURE, SUCCESS, Task } from 'behaviortree'
import { AIBlackboard } from "../blackboard"
import { add, multiply } from "../helper"
import { AI } from "../index"
import { IsVector } from "../utils"

export const BTT_FocusDirection = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const direction = blackboard[blackboardKey];
        if (!direction || !IsVector(direction))
            return FAILURE;

        // TODO: Use vector math library.
        const focalPoint = add(blackboard.input.self.location, multiply(direction, 1000));
        AI.SetFocalPointByLocation(focalPoint);
        return SUCCESS;
    }
});