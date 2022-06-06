import {FAILURE, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_Focus, BTT_StopFocus} from "../tasks/BTT_Focus"
import {BTT_RunEQSQuery} from "../tasks/BTT_RunEQSQuery"
import {EQSQueryType} from "enums"
import {BTT_MoveTo} from "../tasks/BTT_MoveTo"
import {IsSet} from "../decorators/IsSet"
import {AIBlackboard} from "../blackboard"
/*
export const BT_Patrol = new Sequence({
    nodes: [
        BTT_Focus("targetLastKnownLocation"),
        BTT_MoveTo("targetLastKnownLocation")
    ]
})
*/
export const BT_Patrol = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
        BTT_Focus("patrolLocation"),
        BTT_MoveTo("patrolLocation")
    ]
});

/*
export const BT_Patrol = new Sequence({
    nodes: [
        BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
        BTT_Focus("patrolLocation"),
        BTT_MoveTo("patrolLocation"),
        IsSet(new Sequence({
            nodes: [
                BTT_Focus("targetLastKnownLocation"),
                BTT_MoveTo("targetLastKnownLocation"),
                // BTT_Clear
            ]
        }), "targetLastKnownLocation", true)
    ]
});

*/