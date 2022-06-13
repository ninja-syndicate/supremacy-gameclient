import {FAILURE, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_SetFocalPoint, BTT_StopFocus} from "../tasks/BTT_SetFocalPoint"
import {BTT_RunEQSQuery} from "../tasks/BTT_RunEQSQuery"
import {EQSQueryType} from "enums"
import {BTT_MoveTo} from "../tasks/BTT_MoveTo"
import {IsSet} from "../decorators/IsSet"
import { BTT_ClearValue } from '../tasks/BTT_ClearValue'
import { BTT_LookAt } from '../tasks/BTT_LookAt'
import { BTT_StopMoveTo } from '../tasks/BTT_StopMoveTo'
import { AIBlackboard } from '../blackboard'

export const BT_Patrol = new Selector({
    nodes: [
        IsSet(new Sequence({
            nodes: [
                BTT_StopMoveTo(),
                BTT_LookAt("damageStimulusFocalPoint"),
                // TODO: Investigate in the direction of damage stimulus.
                BTT_ClearValue((blackboard: AIBlackboard) => blackboard.damageStimulusFocalPoint = undefined)
            ]
        }), "damageStimulusFocalPoint"),
        IsSet(new Sequence({
            nodes: [
                BTT_RunEQSQuery(EQSQueryType.Patrol, "patrolLocation"),
                BTT_SetFocalPoint("patrolLocation"),
                BTT_MoveTo("patrolLocation"),
                IsSet(new Sequence({
                    nodes: [
                        BTT_SetFocalPoint("targetLastKnownLocation"),
                        BTT_MoveTo("targetLastKnownLocation")
                    ]
                }), "targetLastKnownLocation")
            ]
        }), "damageStimulusFocalPoint", false),   
    ]
});