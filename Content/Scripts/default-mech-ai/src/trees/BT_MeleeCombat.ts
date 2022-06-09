import {FAILURE, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_SetFocalPoint, BTT_StopFocus} from "../tasks/BTT_SetFocalPoint"
import {IsSet} from "../decorators/IsSet"
import {AIBlackboard} from "../blackboard"
import { BTT_SpecialAttack } from '../tasks/BTT_SpecialAttack';
import {Parallel} from 'behaviortree'

export const BT_MeleeCombat = new Parallel({
    nodes: [
        new Selector({
            nodes: [
                //IsSet(BTT_Shoot, "enemyInWeaponLOS", true)
            ]
        }),
        new Sequence({
            nodes: [

                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
                BTT_SetFocalPoint("target"),
                BTT_SpecialAttack("targetLastKnownLocation"),
            ]
        }),
    ],
});