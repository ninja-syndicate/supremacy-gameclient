import {Sequence} from 'behaviortree'
import {BTT_StopFocus} from "../tasks/BTT_Focus"
import {BTT_RunEQSQuery} from "../tasks/BTT_RunEQSQuery"
import {EQSQueryType} from "enums"
import {BTT_MoveTo} from "../tasks/BTT_MoveTo"

export const BT_Patrol = new Sequence({
    nodes: [
        BTT_StopFocus,
        BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
        BTT_MoveTo("patrolLocation"),
    ]
})