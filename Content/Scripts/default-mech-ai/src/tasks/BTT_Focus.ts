import {Task, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index";
import {AIBlackboard} from "../blackboard";

export const BTT_Focus = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        if (typeof blackboard[blackboardKey] !== 'string')
            return FAILURE;
        AI.FocusHash(blackboard[blackboardKey] as string);
        return SUCCESS;
    }
})

export const BTT_StopFocus = new Task({
    run: () => {
        AI.ClearFocus();
        return SUCCESS;
    }
})
