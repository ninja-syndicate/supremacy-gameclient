import {FAILURE, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_Focus, BTT_StopFocus} from "../tasks/BTT_Focus";
import {AIBlackboard} from "../blackboard";

export const BT_Combat = new Selector({
    nodes: [
        new Sequence({
            nodes: [
                new Task({
                    run: (blackboard: AIBlackboard) => {
                        console.log(`canSeeTarget ${blackboard.canSeeTarget}`)
                        return SUCCESS
                    }
                }),
                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
                new Task({
                    run: (blackboard: AIBlackboard) => {
                        console.log("In Main Combat")
                        return SUCCESS
                    }
                }),
                BTT_Focus("targetHash"),
            ]
        }),
    ],
})