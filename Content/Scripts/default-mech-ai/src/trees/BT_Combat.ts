import {FAILURE, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_Focus, BTT_StopFocus} from "../tasks/BTT_Focus"
import {AIBlackboard} from "../blackboard"

export const BT_Combat = new Selector({
    nodes: [
        new Sequence({
            nodes: [
                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
                BTT_Focus("target"),
            ]
        }),
    ],
})