import {FAILURE, Selector, SUCCESS, Task} from 'behaviortree'
import {BT_Combat} from "./BT_Combat";
import {BT_Patrol} from "./BT_Patrol";
import {AIBlackboard} from "../blackboard";

export const BT_Root = new Selector({
    nodes: [
        new Selector({
            nodes: [
                // Has Target
                new Task({
                    run: (blackboard: AIBlackboard) => !!blackboard.targetHash ? SUCCESS : FAILURE
                }),
                BT_Combat,
            ]
        }),
        BT_Patrol,
    ]
})